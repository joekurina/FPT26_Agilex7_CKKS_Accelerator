#include "sycl_ckks_accelerator/ckks_accelerator.h"
#include "common.h"
#include "ifft.h"
#include "allocation.h"
#include "ingress.h"
#include "pipeline_exit.h"
#include "ntt.h"
#include "compute_kernels.h"
#include "interface_checks.h"
#include <sycl/ext/intel/fpga_extensions.hpp>

#include <array>
#include <atomic>
#include <chrono>
#include <cstdio>
#include <cstring>
#include <memory>
#include <optional>
#include <stdexcept>
#include <thread>

using namespace ckks;

namespace {
constexpr size_t coefficients = CHUNK_FRAMES * POLY_N;
constexpr size_t modulus_pipeline_bytes = coefficients * sizeof(uint32_t);
constexpr size_t input_blocks = coefficients / LANES;
constexpr size_t input_bytes = input_blocks * sizeof(PipelineInputBlock);
constexpr size_t c0_blocks = NUM_MODULI * input_blocks;
constexpr size_t c0_bytes = c0_blocks * sizeof(u32x4);
constexpr size_t allocation_alignment = 64;
constexpr std::array<uint32_t, NUM_MODULI> ordered_moduli{
    1053818881u, 1054015489u, 1054212097u,
    1055260673u, 1056178177u, 1056440321u};
using Clock = std::chrono::steady_clock;
using Event = std::optional<sycl::event>;
using OutputEvents = std::array<Event, NUM_MODULI>;
using UniformPolynomials = std::array<std::array<uint32_t, coefficients>, NUM_MODULI>;

int result(uint32_t status, char *text, size_t capacity, const char *message) noexcept {
    if (text && capacity) std::snprintf(text, capacity, "%s", message);
    return static_cast<int>(status);
}

sycl::queue make_queue(sycl::async_handler handler) {
#if FPGA_SIMULATOR
    auto selector = sycl::ext::intel::fpga_simulator_selector_v;
#elif FPGA_HARDWARE
    auto selector = sycl::ext::intel::fpga_selector_v;
#else
    auto selector = sycl::ext::intel::fpga_emulator_selector_v;
#endif
    // Out-of-order, unprofiled: persistent services never complete.
    return sycl::queue{selector, handler};
}


struct Buffer {
    std::unique_ptr<SlotAllocation> memory;
    std::unique_ptr<UniformPolynomials> uniform;
    InputEvents input_kernels;
    std::array<bool, std::tuple_size<InputEvents>::value> input_complete{};
    OutputEvents output_kernels;
    Event download;
    bool occupied = false;
    bool ready = false;
};

} // namespace


struct ckks_accelerator {
    std::atomic<bool> device_failed{false};
    sycl::queue queue;
    std::array<Buffer, RING_SLOTS> buffers;
    InputEvents previous_input;
    OutputEvents previous_output;
    // Ordered acquire/collect wrap independently, and occupied distinguishes full/empty.
    size_t next_buffer = 0;
    size_t next_collect = 0;
    bool failed = false;
    bool closed = false;

    ckks_accelerator()
        : queue(make_queue([this](sycl::exception_list errors) {
              if (errors.size()) device_failed.store(true);
          })) {}

    void check_errors() {
        if (failed) throw std::runtime_error("FPGA accelerator failed");
        queue.throw_asynchronous();
        if (device_failed.load()) throw std::runtime_error("asynchronous FPGA error");
    }
};

namespace {
// Intentionally not a unique_ptr: no static destruction may wait for services.
ckks_accelerator *owner = nullptr;

void require_accelerator(ckks_accelerator *accelerator) {
    if (!accelerator || accelerator != owner || accelerator->closed)
        throw std::invalid_argument("invalid or closed FPGA accelerator");
}

Buffer &oldest_buffer(ckks_accelerator *accelerator) {
    require_accelerator(accelerator);
    auto &buffer = accelerator->buffers[accelerator->next_collect];
    if (!buffer.occupied)
        throw std::invalid_argument("no pending FPGA output");
    return buffer;
}

template<class T> void require_planes(T *const *planes) {
    if (!planes) throw std::invalid_argument("missing polynomial table");
    for (size_t p = 0; p < NUM_MODULI; ++p)
        if (!planes[p]) throw std::invalid_argument("missing polynomial plane");
}

bool has_pending_outputs(const ckks_accelerator &accelerator) {
    for (const auto &buffer : accelerator.buffers)
        if (buffer.occupied) return true;
    return false;
}

// Called from the C entry points' catch blocks. No exception crosses the C ABI.
int report_failure(char *text, size_t capacity) noexcept {
    try {
        throw;
    } catch (const std::invalid_argument &error) {
        return result(CKKS_STATUS_INVALID_ARGUMENT, text, capacity, error.what());
    } catch (const std::exception &error) {
        if (owner) owner->failed = true;
        return result(CKKS_STATUS_RUNTIME_ERROR, text, capacity, error.what());
    } catch (...) {
        if (owner) owner->failed = true;
        return result(CKKS_STATUS_RUNTIME_ERROR, text, capacity, "unknown FPGA runtime error");
    }
}

template<int P> void start_modulus_pipeline(ckks_accelerator &accelerator) {
    constexpr uint32_t modulus = ordered_moduli[P];
    uint32_t ratio[2]{};
    get_barrett_constants(modulus, ratio[0], ratio[1]);
    auto &q = accelerator.queue;
    q.submit([=](sycl::handler &h) { NTTService<P, NTT_A_Tag>{P}(h); });
    q.submit([=](sycl::handler &h) { NTTService<P, NTT_B_Tag>{P}(h); });
    q.submit([=](sycl::handler &h) { ScaleAndReduceKernel<P>(SCALE, modulus, ratio)(h); });
    q.submit([=](sycl::handler &h) { PolyMultNegAddKernel<P>(modulus, ratio)(h); });
}

template<int P>
void launch_output_kernel(ckks_accelerator &accelerator, Buffer &buffer, const OutputEvents &prior) {
    auto *output = static_cast<u32x4 *>(buffer.memory->device_c0());
    buffer.output_kernels[P] = accelerator.queue.submit([&](sycl::handler &h) {
        if (prior[P]) h.depends_on(*prior[P]);
        // Consumers must run while ingress feeds the pipes. Only the previous
        // exit on this modulus pipeline is a prerequisite.
        ExitC0Kernel<P>(output, input_blocks)(h);
    });
}

bool complete(const Event &event) {
    if (!event) throw std::logic_error("missing finite streaming event");
    return event->get_info<sycl::info::event::command_execution_status>() ==
           sycl::info::event_command_status::complete;
}

void launch_chunk(ckks_accelerator &accelerator, Buffer &buffer) {
    const auto prior_input = accelerator.previous_input;
    const auto prior_output = accelerator.previous_output;
    auto &q = accelerator.queue;
    auto &memory = *buffer.memory;
    const auto upload = q.memcpy(memory.device_input(), memory.host_input(), input_bytes);
    launch_output_kernel<0>(accelerator, buffer, prior_output);
    launch_output_kernel<1>(accelerator, buffer, prior_output);
    launch_output_kernel<2>(accelerator, buffer, prior_output);
    launch_output_kernel<3>(accelerator, buffer, prior_output);
    launch_output_kernel<4>(accelerator, buffer, prior_output);
    launch_output_kernel<5>(accelerator, buffer, prior_output);
    // Start this chunk after its upload and the previous chunk's kernels.
    // Its output kernels run concurrently to keep the pipes flowing.
    submit_input(q,
        static_cast<const PipelineInputBlock *>(memory.device_input()),
        input_blocks, {upload, prior_input, prior_output}, buffer.input_kernels);
    const auto current_output = buffer.output_kernels;
    buffer.download = q.submit([&](sycl::handler &h) {
        for (const auto &event : current_output) h.depends_on(*event);
        h.memcpy(memory.host_c0(), memory.device_c0(), c0_bytes);
    });
    accelerator.previous_input = buffer.input_kernels;
    accelerator.previous_output = current_output;
}

bool inputs_finished(Buffer &buffer) {
    bool done = true;
    for (size_t i = 0; i < buffer.input_kernels.size(); ++i) {
        if (!buffer.input_complete[i])
            buffer.input_complete[i] = complete(buffer.input_kernels[i]);
        // Query every unfinished worker, even if an earlier worker is pending.
        done = buffer.input_complete[i] && done;
    }
    return done;
}

bool output_ready(ckks_accelerator &accelerator, Buffer &buffer) {
    // Dispatch asynchronous errors even for completed outputs.
    accelerator.check_errors();
    if (!buffer.ready) {
        // D2H covers all exits. Ingress completion covers the remaining input uses.
        const bool entry_done = inputs_finished(buffer);
        const bool transfer_done = complete(buffer.download);
        accelerator.check_errors();
        buffer.ready = entry_done && transfer_done;
    }
    return buffer.ready;
}

void allocate_buffers(ckks_accelerator &accelerator) {
    for (auto &buffer : accelerator.buffers) {
        buffer.memory = std::make_unique<SlotAllocation>(
            accelerator.queue, input_bytes, c0_bytes, allocation_alignment);
        buffer.uniform = std::make_unique<UniformPolynomials>();
    }
}

void start_kernels(ckks_accelerator &accelerator) {
    accelerator.queue.submit([](sycl::handler &h) { IFFTKernel{}(h); });
    accelerator.queue.submit([](sycl::handler &h) { IFFTFanoutKernel{}(h); });
    start_modulus_pipeline<0>(accelerator);
    start_modulus_pipeline<1>(accelerator);
    start_modulus_pipeline<2>(accelerator);
    start_modulus_pipeline<3>(accelerator);
    start_modulus_pipeline<4>(accelerator);
    start_modulus_pipeline<5>(accelerator);
    accelerator.check_errors();
}

size_t acquire_buffer(ckks_accelerator &accelerator) {
    for (size_t offset = 0; offset < RING_SLOTS; ++offset) {
        const size_t index = (accelerator.next_buffer + offset) % RING_SLOTS;
        auto &buffer = accelerator.buffers[index];
        if (buffer.occupied) continue;
        buffer.occupied = true;
        accelerator.next_buffer = (index + 1) % RING_SLOTS;
        return index;
    }
    return RING_SLOTS;
}

void copy_inputs(Buffer &buffer, const complex_double *encoding, const int8_t *errors,
                 const uint32_t *const *keys, const uint32_t *const *uniform) {
    auto *packed = static_cast<PipelineInputBlock *>(buffer.memory->host_input());
    for (size_t block = 0; block < input_blocks; ++block) {
        pack_encoding_to_block(encoding, block, packed[block].encoding);
        pack_error_to_block(errors, block, packed[block].error);
        for (size_t p = 0; p < NUM_MODULI; ++p) {
            pack_scalar_to_block(keys[p], block, packed[block].secret_key[p]);
            pack_scalar_to_block(uniform[p], block, packed[block].c1[p]);
        }
    }
    for (size_t p = 0; p < NUM_MODULI; ++p)
        std::memcpy((*buffer.uniform)[p].data(), uniform[p], modulus_pipeline_bytes);
}

void copy_outputs(const Buffer &buffer, uint32_t **c0, uint32_t **c1) {
    const auto *packed = static_cast<const u32x4 *>(buffer.memory->host_c0());
    for (size_t p = 0; p < NUM_MODULI; ++p) {
        std::memcpy(c0[p], packed + p * input_blocks, modulus_pipeline_bytes);
        std::memcpy(c1[p], (*buffer.uniform)[p].data(), modulus_pipeline_bytes);
    }
}

void release_buffer(Buffer &buffer) {
    buffer.download.reset();
    buffer.input_kernels.fill(std::nullopt);
    buffer.output_kernels.fill(std::nullopt);
    buffer.input_complete.fill(false);
    buffer.ready = false;
    buffer.occupied = false;
}
} // namespace


extern "C" int ckks_create(
    ckks_accelerator **accelerator, char *text, size_t capacity) try {
    if (!accelerator) throw std::invalid_argument("missing accelerator output");
    *accelerator = nullptr;
    if (owner) throw std::invalid_argument("only one FPGA accelerator per process");
    auto pending = std::make_unique<ckks_accelerator>();
    allocate_buffers(*pending);
    // Persistent kernels never finish. Retain the queue even if startup fails.
    owner = pending.release();
    start_kernels(*owner);
    *accelerator = owner;
    return result(CKKS_STATUS_SUCCESS, text, capacity, "");
} catch (...) {
    return report_failure(text, capacity);
}

extern "C" int ckks_enqueue(ckks_accelerator *accelerator, size_t frames,
    const complex_double *encoding, const int8_t *errors, const uint32_t *const *keys,
    const uint32_t *const *uniform, char *text, size_t capacity) try {
    require_accelerator(accelerator);
    if (frames != CHUNK_FRAMES) throw std::invalid_argument("exactly four frames required");
    if (!encoding || !errors) throw std::invalid_argument("missing input");
    require_planes(keys);
    require_planes(uniform);
    accelerator->check_errors();
    const size_t index = acquire_buffer(*accelerator);
    if (index == RING_SLOTS)
        return result(CKKS_STATUS_BUSY, text, capacity, "both buffers await collection");

    auto &buffer = accelerator->buffers[index];
    copy_inputs(buffer, encoding, errors, keys, uniform);
    // Once submission starts, any exception must retain all live allocations.
    try { launch_chunk(*accelerator, buffer); }
    catch (...) { accelerator->failed = true; throw; }
    accelerator->check_errors();
    return result(CKKS_STATUS_SUCCESS, text, capacity, "");
} catch (...) {
    return report_failure(text, capacity);
}

extern "C" int ckks_poll(ckks_accelerator *accelerator,
    uint32_t *ready, char *text, size_t capacity) try {
    if (!ready) throw std::invalid_argument("missing readiness output");
    *ready = 0;
    auto &buffer = oldest_buffer(accelerator);
    *ready = output_ready(*accelerator, buffer);
    return result(CKKS_STATUS_SUCCESS, text, capacity, "");
} catch (...) {
    return report_failure(text, capacity);
}

extern "C" int ckks_collect_next(ckks_accelerator *accelerator,
    uint32_t **c0, uint32_t **c1, char *text, size_t capacity) try {
    auto &buffer = oldest_buffer(accelerator);
    require_planes(c0);
    require_planes(c1);
    if (!output_ready(*accelerator, buffer))
        return result(CKKS_STATUS_NOT_READY, text, capacity, "FPGA work pending");

    copy_outputs(buffer, c0, c1);
    accelerator->check_errors();
    release_buffer(buffer);
    accelerator->next_collect = (accelerator->next_collect + 1) % RING_SLOTS;
    return result(CKKS_STATUS_SUCCESS, text, capacity, "");
} catch (...) {
    return report_failure(text, capacity);
}

extern "C" int ckks_drain(ckks_accelerator *accelerator, uint64_t timeout_ns,
    char *text, size_t capacity) try {
    require_accelerator(accelerator);
    const auto begin = Clock::now();
    for (;;) {
        accelerator->check_errors();
        bool all_ready = true;
        for (auto &buffer : accelerator->buffers)
            if (buffer.occupied && !output_ready(*accelerator, buffer)) all_ready = false;
        if (all_ready) return result(CKKS_STATUS_SUCCESS, text, capacity, "");

        const auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(Clock::now() - begin).count();
        if (static_cast<uint64_t>(elapsed) >= timeout_ns) {
            accelerator->failed = true;
            return result(CKKS_STATUS_TIMEOUT, text, capacity, "FPGA work timed out");
        }
        std::this_thread::yield();
    }
} catch (...) {
    return report_failure(text, capacity);
}

extern "C" int ckks_close(ckks_accelerator *accelerator, char *text, size_t capacity) try {
    require_accelerator(accelerator);
    accelerator->check_errors();
    if (has_pending_outputs(*accelerator))
        return result(CKKS_STATUS_BUSY, text, capacity, "collect outputs before closing");
    accelerator->closed = true;
    // Free buffers after collection and retain the queue for persistent kernels.
    for (auto &buffer : accelerator->buffers) {
        buffer.memory.reset();
        buffer.uniform.reset();
    }
    return result(CKKS_STATUS_SUCCESS, text, capacity, "");
} catch (...) {
    return report_failure(text, capacity);
}
