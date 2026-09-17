#pragma once

#include "common.h"
#include "pipes.h"
#include "data_types.h"
#include <array>
#include <cstddef>
#include <limits>
#include <optional>
#include <stdexcept>
#include <type_traits>
#include <sycl/sycl.hpp>
#include <sycl/ext/intel/fpga_extensions.hpp>

namespace ckks {
namespace ingress {
inline void validate(const PipelineInputBlock* input, size_t block_count) {
    if (block_count % NUM_BLOCKS != 0)
        throw std::invalid_argument("ingress requires whole frames");
    if (block_count && !input)
        throw std::invalid_argument("ingress requires nonnull input");
    if (block_count > std::numeric_limits<size_t>::max() / sizeof(PipelineInputBlock))
        throw std::overflow_error("ingress input extent overflow");
    // Caller must still establish allocation provenance and H2D completion.
}
constexpr unsigned EncodingDestination = 0;
constexpr unsigned ErrorBegin = EncodingDestination + 1;
constexpr unsigned SecretBegin = ErrorBegin + NUM_MODULI;
constexpr unsigned C1Begin = SecretBegin + NUM_MODULI;
constexpr unsigned DestinationCount = C1Begin + NUM_MODULI;

enum class FieldGroup { Encoding, Error, Secret, C1 };
template <unsigned D, FieldGroup Group =
    (D < ErrorBegin ? FieldGroup::Encoding :
     D < SecretBegin ? FieldGroup::Error :
     D < C1Begin ? FieldGroup::Secret : FieldGroup::C1)>
struct DestinationFields;
template <unsigned D> struct DestinationFields<D, FieldGroup::Encoding> {
    static_assert(D < DestinationCount, "invalid ingress destination");
    using Payload = encoding_block;
    using ProductionPipe = SharedToIFFTPipe;
    static Payload extract(const PipelineInputBlock& block) { return block.encoding; }
};
template <unsigned D> struct DestinationFields<D, FieldGroup::Error> {
    static_assert(D < DestinationCount, "invalid ingress destination");
    using Payload = i8x4;
    using ProductionPipe = ErrorToScaleReducePipes::PipeAt<D - ErrorBegin>;
    static Payload extract(const PipelineInputBlock& block) { return block.error; }
};
template <unsigned D> struct DestinationFields<D, FieldGroup::Secret> {
    static_assert(D < DestinationCount, "invalid ingress destination");
    using Payload = u32x4;
    using ProductionPipe = typename PipeSet<D - SecretBegin>::EntryToNTTAPipe;
    static Payload extract(const PipelineInputBlock& block) { return block.secret_key[D - SecretBegin]; }
};
template <unsigned D> struct DestinationFields<D, FieldGroup::C1> {
    static_assert(D < DestinationCount, "invalid ingress destination");
    using Payload = u32x4;
    using ProductionPipe = typename PipeSet<D - C1Begin>::EntryToPolyMultNegPipe;
    static Payload extract(const PipelineInputBlock& block) { return block.c1[D - C1Begin]; }
};
// One writer/reader per bank/destination queue. Reserve a full frame.
template <unsigned Bank, unsigned D> class BankDestinationPipeID;
template <unsigned D> class AcceptedPipeID;
template <unsigned Bank> class ReleasePipeID;
template <unsigned Bank, unsigned D> using BankDestinationPipe = sycl::ext::intel::pipe<
    BankDestinationPipeID<Bank, D>, typename DestinationFields<D>::Payload, NUM_BLOCKS>;
template <unsigned D> using Accepted = sycl::ext::intel::pipe<AcceptedPipeID<D>, bool, 2>;
template <unsigned Bank> using ReleasePipe = sycl::ext::intel::pipe<ReleasePipeID<Bank>, bool, 1>;
// Statically expanded, ascending calls. Each call completes before the next.
// Shared by lane/modulus accesses and the three destination-order operations.
template <unsigned Count, unsigned I = 0, typename Function>
inline void ordered_indices(Function&& function) {
    if constexpr (I < Count) {
        function(std::integral_constant<unsigned, I>{});
        ordered_indices<Count, I + 1>(function);
    }
}

// Payloads are packed structs, not indexable vectors. Copy fields by value:
// never bind a reference to a packed scalar member or change the payload ABI.
template <unsigned Lane, typename Vector>
inline auto read_lane(const Vector& vector) {
    static_assert(LANES == 4 && Lane < LANES);
    if constexpr (Lane == 0) return vector.element0;
    else if constexpr (Lane == 1) return vector.element1;
    else if constexpr (Lane == 2) return vector.element2;
    else return vector.element3;
}
template <unsigned Lane, typename Vector, typename Scalar>
inline void write_lane(Vector& vector, Scalar value) {
    static_assert(LANES == 4 && Lane < LANES);
    if constexpr (Lane == 0) vector.element0 = value;
    else if constexpr (Lane == 1) vector.element1 = value;
    else if constexpr (Lane == 2) vector.element2 = value;
    else vector.element3 = value;
}
} // namespace ingress

// Each specialization owns one fixed bank and disjoint RAM.
template <unsigned Bank> class InputBank {
    static_assert(Bank < 2);
    const PipelineInputBlock* input_;
    size_t block_count_;
public:
    InputBank(const PipelineInputBlock* input, size_t block_count)
        : input_(input), block_count_(block_count) {}
    [[intel::kernel_args_restrict]]
    void operator()() const {
        const size_t frame_count = block_count_ / NUM_BLOCKS;
        using namespace ingress;
        using sycl::ext::intel::fpga_reg;
        sycl::ext::intel::device_ptr<const PipelineInputBlock> input(input_);
        // Constant lane/modulus accesses expose parallel scalar storage.
        // Multidimensional RAM inference/II still requires a compiler report.
        [[intel::fpga_memory]] double encoding_real[LANES][NUM_BLOCKS];
        [[intel::fpga_memory]] double encoding_imag[LANES][NUM_BLOCKS];
        [[intel::fpga_memory]] int8_t error[LANES][NUM_BLOCKS];
        [[intel::fpga_memory]] uint32_t secret_key[NUM_MODULI][LANES][NUM_BLOCKS];
        [[intel::fpga_memory]] uint32_t c1[NUM_MODULI][LANES][NUM_BLOCKS];

        [[intel::disable_loop_pipelining]]
        for (size_t frame = Bank; frame < frame_count;) {
            // Fill without pipe backpressure.
            [[intel::nofusion]] [[intel::initiation_interval(1)]]
            for (size_t block_index = 0; block_index < NUM_BLOCKS; ++block_index) {
                const PipelineInputBlock block = input[frame * NUM_BLOCKS + block_index];
                ordered_indices<LANES>([&](auto lane) {
                    constexpr unsigned L = decltype(lane)::value;
                    encoding_real[L][block_index] = read_lane<L>(block.encoding).real();
                    encoding_imag[L][block_index] = read_lane<L>(block.encoding).imag();
                    error[L][block_index] = read_lane<L>(block.error);
                });
                ordered_indices<NUM_MODULI>([&](auto modulus) {
                    constexpr unsigned M = decltype(modulus)::value;
                    ordered_indices<LANES>([&](auto lane) {
                        constexpr unsigned L = decltype(lane)::value;
                        secret_key[M][L][block_index] = read_lane<L>(block.secret_key[M]);
                        c1[M][L][block_index] = read_lane<L>(block.c1[M]);
                    });
                });
            }
            // Full-frame FIFOs let these blocking writes stall safely.
            [[intel::nofusion]] [[intel::initiation_interval(1)]]
            for (size_t block_index = 0; block_index < NUM_BLOCKS; ++block_index) {
                PipelineInputBlock block{};
                ordered_indices<LANES>([&](auto lane) {
                    constexpr unsigned L = decltype(lane)::value;
                    write_lane<L>(block.encoding, complex_double(
                        fpga_reg(encoding_real[L][block_index]), fpga_reg(encoding_imag[L][block_index])));
                    write_lane<L>(block.error, fpga_reg(error[L][block_index]));
                });
                ordered_indices<NUM_MODULI>([&](auto modulus) {
                    constexpr unsigned M = decltype(modulus)::value;
                    ordered_indices<LANES>([&](auto lane) {
                        constexpr unsigned L = decltype(lane)::value;
                        write_lane<L>(block.secret_key[M], fpga_reg(secret_key[M][L][block_index]));
                        write_lane<L>(block.c1[M], fpga_reg(c1[M][L][block_index]));
                    });
                });
                ordered_indices<DestinationCount>([&](auto destination) {
                    constexpr unsigned D = decltype(destination)::value;
                    BankDestinationPipe<Bank, D>::write(DestinationFields<D>::extract(block));
                });
            }
            // Consume the final ACK before reuse, including on the last frame.
            (void)ReleasePipe<Bank>::read();
            frame = frame_count - frame > 2 ? frame + 2 : frame_count;
        }
    }
};

namespace ingress {
// Bank selection stays outside the block loop. FIFO order pairs fields downstream.
template <unsigned Bank, unsigned D>
inline void emit_frame() {
    static_assert(Bank < 2 && D < DestinationCount);
    using ProductionPipe = typename DestinationFields<D>::ProductionPipe;
    [[intel::nofusion]] [[intel::initiation_interval(1)]]
    for (size_t block_index = 0; block_index < NUM_BLOCKS; ++block_index) {
        const auto payload = BankDestinationPipe<Bank, D>::read();
        ProductionPipe::write(payload);
    }
}
} // namespace ingress

template <unsigned D> class InputForwarder {
    static_assert(D < ingress::DestinationCount);
    size_t block_count_;
public:
    explicit InputForwarder(size_t block_count) : block_count_(block_count) {}
    void operator()() const {
        const size_t frame_count = block_count_ / NUM_BLOCKS;
        using namespace ingress;
        [[intel::disable_loop_pipelining]]
        for (size_t frame = 0; frame < frame_count; ++frame) {
            if (frame & 1u) emit_frame<1, D>();
            else emit_frame<0, D>();
            // Acknowledge only after the final production write is accepted.
            Accepted<D>::write(true);
        }
    }
};

class InputBankRelease {
    size_t block_count_;
public:
    explicit InputBankRelease(size_t block_count) : block_count_(block_count) {}
    void operator()() const {
        const size_t frame_count = block_count_ / NUM_BLOCKS;
        using namespace ingress;
        [[intel::disable_loop_pipelining]]
        for (size_t frame = 0; frame < frame_count; ++frame) {

            ordered_indices<DestinationCount>([](auto destination) {
                constexpr unsigned D = decltype(destination)::value;
                (void)Accepted<D>::read();
            });
            // Reuse follows every destination acceptance. Control pipes start empty.
            if (frame & 1u) ReleasePipe<1>::write(true);
            else ReleasePipe<0>::write(true);
        }
    }
};

// Event slots: banks 0/1, forwarder D at 2+D, release last.
// A completed invocation leaves data/Accepted/Release pipes empty.
using InputEvents = std::array<std::optional<sycl::event>,
    2 + ingress::DestinationCount + 1>;
// Publish each event before the next submit. On failure retain storage/queue,
// poison the owner, and never wait on or retry a partial graph.
// Dependencies cover upload and prior chunks only, never current pipe peers.
struct IngressPrerequisites {
    const sycl::event& upload;
    const InputEvents& prior_input;
    const std::array<std::optional<sycl::event>, NUM_MODULI>& prior_output;

    void operator()(sycl::handler& h) const {
        h.depends_on(upload);
        for (const auto& event : prior_input) if (event) h.depends_on(*event);
        for (const auto& event : prior_output) if (event) h.depends_on(*event);
    }
};

inline void submit_input(
    sycl::queue& q, const PipelineInputBlock* input, size_t block_count,
    const IngressPrerequisites& prerequisites, InputEvents& events) {
    ingress::validate(input, block_count);
    if (q.has_property<sycl::property::queue::in_order>())
        throw std::invalid_argument("ingress requires an out-of-order queue");
    for (const auto& event : events)
        if (event) throw std::invalid_argument("ingress event storage must be empty");
    using namespace ingress;

    // Named device functors also supply the SYCL kernel identities.
    events[0] = q.submit([&](sycl::handler& h) {
        prerequisites(h); h.single_task(InputBank<0>{input, block_count});
    });
    events[1] = q.submit([&](sycl::handler& h) {
        prerequisites(h); h.single_task(InputBank<1>{input, block_count});
    });

    ordered_indices<DestinationCount>([&](auto destination) {
        constexpr unsigned D = decltype(destination)::value;
        events[2 + D] = q.submit([&](sycl::handler& h) {
            prerequisites(h);
            h.single_task(InputForwarder<D>{block_count});
        });
    });

    events[2 + DestinationCount] = q.submit([&](sycl::handler& h) {
        prerequisites(h); h.single_task(InputBankRelease{block_count});
    });
}

} // namespace ckks
