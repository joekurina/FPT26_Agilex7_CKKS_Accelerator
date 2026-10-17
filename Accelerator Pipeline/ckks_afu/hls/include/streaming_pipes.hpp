#pragma once

#include "parameters.hpp"
#include <sycl/ext/altera/experimental/pipes_ext.hpp>
#include <sycl/ext/altera/fpga_extensions.hpp>
#include <sycl/sycl.hpp>
#include "ckks_native.h"

namespace ckks {
    // Shared payload formats and channels. Stage implementations perform the
    // reads/writes. ckks_pipeline.cpp starts and joins the communicating tasks.
    namespace altera = sycl::ext::altera::experimental;
    namespace properties = sycl::ext::oneapi::experimental;

    // One block of signed coefficients after IFFT scaling, rounding and error
    // addition. Each message-role NTT reduces its copy before the transform.
    struct SignedCoefficientBlock {
        std::int64_t lane[coefficient_lanes];
    };

    // Signed error samples paired with the corresponding IFFT call.
    struct ErrorBlock {
        std::int8_t lane[coefficient_lanes];
    };

    // Coefficients for one modulus. The pipe determines whether these are
    // coefficient-domain values or NTT-domain values.
    struct CoefficientBlock {
        std::uint32_t lane[coefficient_lanes];
    };

    // decltype names the compile-time property-set type for external ports.
    // The first five entries retain the documented Avalon streaming defaults.
    // protocol_axi_streaming selects AXI here, with TVALID/TREADY handshaking.
    // This exact type is part of the port names in ckks_pipeline_binding.sv.
    using AxiStreamProperties = decltype(properties::properties(
        altera::ready_latency<0>,
        altera::bits_per_symbol<8>,
        altera::uses_valid<true>,
        altera::uses_ready<true>,
        altera::first_symbol_in_high_order_bits<false>,
        altera::protocol_axi_streaming));

    // External pipe capacity zero leaves buffering to the compiler.
    inline constexpr std::size_t pipe_capacity = 0;

    // Reuse the packed host input layout: one encoding/error block plus the
    // key and C1 blocks for all moduli and a reserved field. In the current
    // layout, each 264-byte record spans multiple 64-byte DMA words.
    using InputRecord = ckks_native_input_record;
    // One complex value is a pair of binary64 real/imaginary components.
    using ComplexValue = ckks_native_complex64;

    // Four complex values from ingress to the imported IFFT input.
    struct ComplexBlock {
        ComplexValue lane[coefficient_lanes];
    };

    // Raw 512-bit input payload. The parser reassembles InputRecords from it.
    struct DmaWord {
        std::uint8_t byte[64];
    };

    // Four coefficient blocks from one C0 modulus plane. With four lanes,
    // this packs 16 uint32 coefficients into one 512-bit output payload.
    struct ResultWord {
        CoefficientBlock block[4];
    };

    // Parser error flags: bit 0 marks a nonzero InputRecord::reserved field.
    // PipelineFrame emits this once after all of its stage tasks have joined.
    struct FrameStatus {
        std::uint32_t errors;
    };

    // Forward-declared types uniquely identify channels. Each Modulus*PipeId<P>
    // specialization names a distinct pipe for modulus index P.
    class DmaInputId;
    class DmaOutputId;
    class FrameStatusId;
    class InputRecordsId;
    class EncodingInputId;
    class IfftErrorId;
    class IfftOutputId;
    template <std::size_t P> class ModulusMessagePipeId;
    template <std::size_t P> class ModulusKeyPipeId;
    template <std::size_t P> class ModulusC1PipeId;
    template <std::size_t P> class ModulusKeyNttPipeId;
    template <std::size_t P> class ModulusMessageNttPipeId;
    template <std::size_t P> class ModulusC0PipeId;

    // AXI beat wrappers add TLAST to tdata by default. TVALID/TREADY are
    // interface handshake signals.
    using DmaInputBeat = altera::StreamingBeatAxi<DmaWord>;
    using DmaOutputBeat = altera::StreamingBeatAxi<ResultWord>;
    using StatusBeat = altera::StreamingBeatAxi<FrameStatus>;

    // AFU DMA input to parser. Parsing uses a fixed word count.
    using DmaInput = altera::pipe<DmaInputId, DmaInputBeat, pipe_capacity, AxiStreamProperties>;
    // Egress to AFU DMA output. TLAST marks the final word of the last C0 plane.
    using DmaOutput = altera::pipe<DmaOutputId, DmaOutputBeat, pipe_capacity, AxiStreamProperties>;
    // PipelineFrame to AFU status input: one status beat with TLAST per frame.
    using StatusOutput = altera::pipe<FrameStatusId, StatusBeat, 1, AxiStreamProperties>;

    // Internal pipes use the default inter-kernel protocol and plain payloads.
    // Frames are counted by stage loops. The compiler may provide more capacity.
    // Blocking reads wait for data. Blocking writes wait for space.

    // All downstream FIFOs retain blocks_per_frame entries: a complete frame.
    // Parser to input distributor: reassembled packed input records.
    using InputRecords = altera::pipe<InputRecordsId, InputRecord, blocks_per_frame>;
    // Input distributor to IFFT: complex encoding input.
    using EncodingInput = altera::pipe<EncodingInputId, ComplexBlock, blocks_per_frame>;
    // Input distributor to the IFFT adapter: coefficient-order errors. A full
    // frame can queue. The IFFT task owns one error block per call.
    using IfftError = altera::pipe<IfftErrorId, ErrorBlock, blocks_per_frame>;
    // IFFT to fan-out: shared scaled, rounded and error-added signed values.
    // Retain the full-frame FIFO and separate blocking fan-out task.
    using IfftOutput = altera::pipe<IfftOutputId, SignedCoefficientBlock, blocks_per_frame>;

    // One independent FIFO set per RNS modulus index P (currently 0 through 5).
    // P selects the modulus. Each payload carries coefficient_lanes values,
    // and each FIFO requests a full frame of blocks.
    template <std::size_t P> struct ModulusPipes {
        // IFFT fan-out directly to the message-role NTT. That task reduces the
        // shared signed value modulo q_P before forming the imported NTT request.
        using message = altera::pipe<ModulusMessagePipeId<P>, SignedCoefficientBlock, blocks_per_frame>;
        // Input distributor to the key NTT: secret-key coefficients for P.
        using key = altera::pipe<ModulusKeyPipeId<P>, CoefficientBlock, blocks_per_frame>;
        // Input distributor to polynomial_frame<P>: supplied C1 coefficients.
        using c1 = altera::pipe<ModulusC1PipeId<P>, CoefficientBlock, blocks_per_frame>;
        // Key NTT to polynomial_frame<P>: transformed secret-key coefficients.
        using key_ntt = altera::pipe<ModulusKeyNttPipeId<P>, CoefficientBlock, blocks_per_frame>;
        // Message NTT to polynomial_frame<P>: transformed scaled/noisy message.
        using message_ntt = altera::pipe<ModulusMessageNttPipeId<P>, CoefficientBlock, blocks_per_frame>;
        // Polynomial arithmetic to egress: C0 = message_ntt - key_ntt * C1 mod q_P.
        using c0 = altera::pipe<ModulusC0PipeId<P>, CoefficientBlock, blocks_per_frame>;
    };
} // namespace ckks
