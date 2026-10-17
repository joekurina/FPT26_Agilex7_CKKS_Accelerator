// Hardware-only OPAE transport for the single-admission native CKKS frame interface.
// Uncertain DMA ownership enters the retained-owner hold path.

#include "benchmark.hpp"
#include "ckks_native.h"
#include "ckks_afu_identity.hpp"
#include <opae/fpga.h>


#include <array>
#include <atomic>
#include <charconv>
#include <chrono>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <unistd.h>

namespace {
using Clock = std::chrono::steady_clock;
// One registered allocation contains page-aligned input and output payloads.
constexpr std::size_t allocation_bytes = 2 * 1024 * 1024;
constexpr std::size_t input_offset = 4096;
constexpr std::size_t output_offset = input_offset + CKKS_NATIVE_INPUT_BYTES + 4096;
static_assert(CKKS_NATIVE_INPUT_BYTES % 4096 == 0 && CKKS_NATIVE_C0_BYTES % 4096 == 0);
static_assert(output_offset + CKKS_NATIVE_C0_BYTES < allocation_bytes);

// Known-state and argument failures use the ordinary exception-reporting path.
void require(bool condition, const char* message) {
    if (!condition) throw std::runtime_error(message);
}
// Retain the allocation and SDK handles/FDs while the process remains alive.
// DMA activity remains uncertain. SIGCONT returns to the SIGSTOP loop.
[[noreturn]] void hold_owner(const char* reason, std::uint64_t sequence, std::uint64_t status) noexcept {
    std::fprintf(stderr, "HOLD_UNKNOWN_DMA pid=%ld sequence=%llu status=0x%016llx reason=%s; "
        "process, buffers and FDs retained; no further device access or cleanup.\n",
        static_cast<long>(getpid()), static_cast<unsigned long long>(sequence),
        static_cast<unsigned long long>(status), reason);
    std::fflush(stderr);
    for (;;) if (raise(SIGSTOP)) pause();
}
// Block maskable signals for the DMA owner. Selected termination requests are
// polled at quiescent frame boundaries.
void protect_signals() {
    sigset_t signals;
    require(sigfillset(&signals) == 0 && sigprocmask(SIG_BLOCK, &signals, nullptr) == 0,
            "Cannot block signals for the DMA owner");
}

// Require full consumption and the caller's upper bound.
unsigned parse_unsigned(const std::string& value, unsigned maximum, int base = 10) {
    unsigned parsed = 0;
    const auto result = std::from_chars(value.data(), value.data() + value.size(), parsed, base);
    require(!value.empty() && result.ec == std::errc{} && result.ptr == value.data() + value.size()
            && parsed <= maximum, "Invalid numeric argument");
    return parsed;
}
struct PciAddress {
    std::uint16_t segment;
    std::uint8_t bus, device, function;
};
// Parse only the exact domain:bus:device.function spelling and PCI field ranges.
PciAddress parse_bdf(const std::string& value) {
    require(value.size() == 12 && value[4] == ':' && value[7] == ':' && value[10] == '.',
            "BDF must use exact dddd:bb:dd.f syntax");
    return {static_cast<std::uint16_t>(parse_unsigned(value.substr(0,4), 65535, 16)),
            static_cast<std::uint8_t>(parse_unsigned(value.substr(5,2), 255, 16)),
            static_cast<std::uint8_t>(parse_unsigned(value.substr(8,2), 31, 16)),
            static_cast<std::uint8_t>(parse_unsigned(value.substr(11,1), 7, 16))};
}

// Own the AFU handle, MMIO mapping and one pinned allocation across all frames.
// Resource flags track teardown attempts, while go_possible blocks uncertain teardown.
class Device {
    fpga_properties properties = nullptr;
    fpga_token token = nullptr;
    fpga_handle handle = nullptr;
    bool mapped = false, prepared = false, configured = false;
    bool go_possible = false;
    void* allocation = nullptr;
    std::uint64_t wsid = 0, base_iova = 0, input_iova = 0, output_iova = 0;
    std::uint64_t sequence = 0, last_status = 0;
    std::array<std::uint64_t, 8> words{};

    // An SDK failure after GO may leave DMA active, even if the call itself failed.
    // Before that boundary, throw and let cleanup handle the resources acquired so far.
    void check(fpga_result result, const char* operation) {
        if (result != FPGA_OK) {
            if (go_possible) hold_owner(operation, sequence, last_status);
            throw std::runtime_error(std::string(operation) + " rc=" + std::to_string(result));
        }
    }
    // Use 64-bit accesses to MMIO region zero, with byte offsets from ckks_csr.sv.
    std::uint64_t read(std::uint64_t offset) {
        std::uint64_t value = 0;
        check(fpgaReadMMIO64(handle, 0, offset, &value), "fpgaReadMMIO64");
        return value;
    }
    // Route write failures through the same GO-sensitive ownership policy as reads.
    void write(std::uint64_t offset, std::uint64_t value) {
        check(fpgaWriteMMIO64(handle, 0, offset, value), "fpgaWriteMMIO64");
    }
    // Return pointers to the allocation's input and output payload subranges.
    std::uint8_t* input() { return static_cast<std::uint8_t*>(allocation) + input_offset; }
    std::uint8_t* output() { return static_cast<std::uint8_t*>(allocation) + output_offset; }

public:
    // The Device's SDK resources have a single cleanup owner.
    Device() = default;
    Device(const Device&) = delete;
    Device& operator=(const Device&) = delete;
    // Fallback cleanup runs during unwinding and discards its boolean result.
    ~Device() { cleanup(); }

    // Select one exact AFU, validate its MMIO ABI, then register and lock DMA ranges.
    void open(const PciAddress& bdf) {
        check(fpgaGetProperties(nullptr, &properties), "fpgaGetProperties");
        // Parse the generated textual UUID into bytes for the enumeration filter.
        fpga_guid guid{};
        const std::string uuid = CKKS_AFU_UUID;
        std::size_t position = 0;
        for (auto& byte : guid) {
            if (position == 8 || position == 13 || position == 18 || position == 23) ++position;
            byte = static_cast<std::uint8_t>(parse_unsigned(uuid.substr(position, 2), 255, 16));
            position += 2;
        }
        // Match the requested BDF and AFU UUID.
        check(fpgaPropertiesSetObjectType(properties, FPGA_ACCELERATOR), "set object type");
        check(fpgaPropertiesSetGUID(properties, guid), "set UUID");
        check(fpgaPropertiesSetSegment(properties, bdf.segment), "set segment");
        check(fpgaPropertiesSetBus(properties, bdf.bus), "set bus");
        check(fpgaPropertiesSetDevice(properties, bdf.device), "set device");
        check(fpgaPropertiesSetFunction(properties, bdf.function), "set function");
        std::uint32_t matches = 0;
        check(fpgaEnumerate(&properties, 1, &token, 1, &matches), "fpgaEnumerate");
        require(matches == 1, "Expected exactly one CKKS AFU at selected BDF");
        check(fpgaOpen(token, &handle, 0), "fpgaOpen");
        check(fpgaMapMMIO(handle, 0, nullptr), "fpgaMapMMIO");
        mapped = true;
        // Check the native interface and payload sizes before configuring DMA.
        require(read(0x028) == UINT64_C(0x434b4b534e415431) &&
                read(0x030) == ((UINT64_C(1) << 32) | (UINT64_C(1) << 16) | 1) &&
                read(0x120) == ((std::uint64_t(CKKS_NATIVE_C0_BYTES) << 32) | CKKS_NATIVE_INPUT_BYTES),
                "CKKS identity/ABI mismatch");
        // Refuse to reuse a device with prior busy/done, error or configuration-lock state.
        require(read(0x080) == 0 && read(0x088) == 0 && read(0x118) == 0,
                "AFU must be clean, idle and unlocked before allocation");
        sequence = read(0x038);
        // Register memory with OPAE, then obtain its device-visible IOVA.
        check(fpgaPrepareBuffer(handle, allocation_bytes, &allocation, &wsid, 0), "fpgaPrepareBuffer");
        prepared = true;
        check(fpgaGetIOAddress(handle, wsid, &base_iova), "fpgaGetIOAddress");
        require((base_iova & 4095) == 0 &&
                base_iova <= (UINT64_C(1) << 57) - allocation_bytes, "IOVA range/alignment");
        // Registered subranges make both payload addresses nonzero even when the
        // backend legitimately assigns IOVA zero to the allocation's first page.
        input_iova = base_iova + input_offset;
        output_iova = base_iova + output_offset;
        // Touch the registered allocation before warmup and publish its payload ranges.
        // The packed capacity word has output bytes above input bytes.
        std::memset(allocation, 0, allocation_bytes);
        write(0x100, input_iova);
        write(0x108, output_iova);
        write(0x110, (std::uint64_t(CKKS_NATIVE_C0_BYTES) << 32) | CKKS_NATIVE_INPUT_BYTES);
        // Mark cleanup responsible before the lock write or its readback can fail.
        configured = true;
        write(0x118, 1);
        require(read(0x118) == 1 && read(0x088) == 0, "AFU configuration rejected");
        // Command words hold sequence, input/output IOVAs, packed lengths, slot/flags
        // and ABI. Zero initialization preserves all slot/flags and reserved fields.
        // execute refreshes the sequence for each submission.
        words[1] = input_iova;
        words[2] = output_iova;
        words[3] = (std::uint64_t(CKKS_NATIVE_C0_BYTES) << 32) | CKKS_NATIVE_INPUT_BYTES;
        words[5] = CKKS_NATIVE_ABI_VERSION;
    }

    // Synchronously return C0 only after matching completion and observed idle.
    // The allocation remains registered for reuse until device cleanup.
    const std::uint8_t* execute(const std::uint8_t* source, std::size_t bytes) {
        require(source && bytes == CKKS_NATIVE_INPUT_BYTES && configured && !go_possible,
                "Invalid frame submission");
        require(sequence != std::numeric_limits<std::uint64_t>::max(), "Sequence exhausted");
        // Honor cooperative stop requests before copying input or risking another GO.
        sigset_t pending;
        require(sigpending(&pending) == 0, "Cannot inspect cooperative stop request");
        require(!sigismember(&pending, SIGINT) && !sigismember(&pending, SIGTERM) &&
                !sigismember(&pending, SIGHUP) && !sigismember(&pending, SIGQUIT),
                "Cooperative stop at quiescent frame boundary");
        std::memcpy(input(), source, bytes);
        words[0] = ++sequence;
        // Stage all eight command words before the sequence-valued GO doorbell.
        for (std::size_t i = 0; i < words.size(); ++i) write(0x040 + 8 * i, words[i]);
        // Order host writes before GO. The device's later completion fence is separate.
        std::atomic_thread_fence(std::memory_order_seq_cst);
        const auto deadline = Clock::now() + std::chrono::seconds(5);
        // Set this before the GO write, whose acceptance remains uncertain on MMIO failure.
        go_possible = true;
        write(0x080, sequence);
        for (;;) {
            // Status is frame_errors in the upper word, DONE in bit 1 and BUSY in bit 0.
            last_status = read(0x080);
            // DONE precedes fault/deadline checks, so completed error frames use release.
            if (last_status & 2) break;
            // Before DONE, faults or timeout enter the retained-owner hold path.
            if ((last_status >> 32) != 0) hold_owner("Frame fault before fenced completion", sequence, last_status);
            if (Clock::now() >= deadline) hold_owner("Frame completion deadline", sequence, last_status);
        }
        // RTL asserts DONE after its explicit DMA fence succeeds.
        // A different completion sequence still leaves this submission's ownership uncertain.
        if (read(0x038) != sequence) hold_owner("Completion sequence mismatch", sequence, last_status);
        // Combine hardware frame/parser and CSR/admin errors.
        const auto errors = (last_status >> 32) | read(0x088);
        // Keep subsequent host memory consumption ordered after the completion observation.
        std::atomic_thread_fence(std::memory_order_seq_cst);
        // Release frame admission while retaining DMA storage. Reuse the original five-second
        // deadline, checking it only while either BUSY or DONE remains set.
        // The idle loop's hold diagnostic still uses the pre-release last_status snapshot.
        write(0x090, sequence);
        while (read(0x080) & 3) {
            if (Clock::now() >= deadline) hold_owner("Release/idle deadline", sequence, last_status);
        }
        // Only observed idle permits ordinary exception cleanup. Completed error frames
        // are rejected after release.
        go_possible = false;
        require(errors == 0, "Completed frame reported hardware/CSR errors");
        return output();
    }

    // Uncertain GO ownership enters the retained-owner hold path.
    bool cleanup() noexcept {
        if (go_possible) hold_owner("Cleanup with uncertain DMA", sequence, last_status);
        bool ok = true;
        // Accumulate resource-release errors for the cleanup result.
        auto close_result = [&](fpga_result rc, const char* name) {
            if (rc != FPGA_OK) { std::fprintf(stderr, "CLEANUP_ERROR operation=%s rc=%d\n", name, int(rc)); ok = false; }
        };
        // If configured, require observed idle and confirmed unlock or quarantine the owner.
        if (configured) {
            std::uint64_t status = 0, lock = 1;
            if (fpgaReadMMIO64(handle, 0, 0x080, &status) != FPGA_OK || (status & 3))
                hold_owner("Final idle unavailable", sequence, status);
            if (fpgaWriteMMIO64(handle, 0, 0x118, 0) != FPGA_OK ||
                fpgaReadMMIO64(handle, 0, 0x118, &lock) != FPGA_OK || lock != 0)
                hold_owner("Final configuration unlock unavailable", sequence, status);
            configured = false;
        }
        // Continue through all remaining resource-release attempts on failure.
        // Flags/handles are cleared as attempts are made, giving each operation one attempt.
        // A false result leaves resource-release outcomes uncertain.
        if (prepared) { prepared = false; close_result(fpgaReleaseBuffer(handle, wsid), "release buffer"); }
        if (mapped) { mapped = false; close_result(fpgaUnmapMMIO(handle, 0), "unmap MMIO"); }
        if (handle) { const auto h = handle; handle = nullptr; close_result(fpgaClose(h), "close handle"); }
        if (token) { close_result(fpgaDestroyToken(&token), "destroy token"); token = nullptr; }
        if (properties) { close_result(fpgaDestroyProperties(&properties), "destroy properties"); properties = nullptr; }
        return ok;
    }
};
// Adapt the concrete owner to the backend-neutral benchmark callback.
const std::uint8_t* submit(void* context, const std::uint8_t* input, std::size_t bytes) {
    return static_cast<Device*>(context)->execute(input, bytes);
}
}

// Validate CLI paths and hardware preconditions for the native benchmark.
// Normal failures are reported here.
int main(int argc, char** argv) {
    try {
        if (argc == 2 && std::strcmp(argv[1], "--help") == 0) {
            std::cout << "Usage: ckks_native_benchmark dddd:bb:dd.f compact-key SEAL-key [frames trials]\n"
                      << "OPAE configuration: LIBOPAE_CFGFILE or the system default.\n"
                      << "Hardware-only. Exact AFU UUID: " << CKKS_AFU_UUID << '\n';
            return 0;
        }
        require(argc == 4 || argc == 6, "Use --help for arguments");
        const auto bdf = parse_bdf(argv[1]);
        ckks::NativeBenchmarkOptions options;
        options.compact_key = argv[2]; options.seal_key = argv[3];
        if (argc == 6) {
            options.frames = parse_unsigned(argv[4], 1000000);
            options.repetitions = parse_unsigned(argv[5], 100);
        }
        require(options.frames >= 3 && options.repetitions > 0, "Invalid benchmark bounds");
        require(std::getenv("WITH_ASE") == nullptr, "Use the hardware OPAE backend for benchmarks");
        // Establish the DMA owner's signal policy before opening the AFU.
        protect_signals();
        Device device;
        device.open(bdf);
        const int result = ckks::run_native_benchmark(options, submit, &device);
        // Report completion after checked device cleanup.
        require(device.cleanup(), "OPAE cleanup failed");
        std::cout << "NATIVE_BENCHMARK_COMPLETE cleanup_passed=1" << std::endl;
        return result;
    } catch (const std::exception& error) {
        std::cerr << "NATIVE_BENCHMARK_FAILED " << error.what() << std::endl;
        return 1;
    }
}
