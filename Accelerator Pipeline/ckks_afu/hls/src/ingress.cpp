#include "ingress.hpp"
#include "streaming_pipes.hpp"
#include <cstring>
#include <numeric>

namespace ckks {
    // A tile contains a whole number of both DMA words and input records.
    // The current layout groups eight 264-byte records into 33 64-byte words.
    inline constexpr std::size_t record_word_gcd = std::gcd(sizeof(InputRecord), sizeof(DmaWord));
    inline constexpr std::size_t records_per_tile = sizeof(DmaWord) / record_word_gcd;
    inline constexpr std::size_t words_per_tile = sizeof(InputRecord) / record_word_gcd;

    // Parse a fixed frame length by word count.
    inline std::uint32_t parse_input_frame() {
        std::uint32_t errors = 0;

        // blocks_per_frame must be divisible by records_per_tile.
        for (std::size_t tile = 0; tile < blocks_per_frame / records_per_tile; ++tile) {
            DmaWord words[words_per_tile];

            [[intel::initiation_interval(1)]]
            for (std::size_t word = 0; word < words_per_tile; ++word)
                words[word] = DmaInput::read().tdata;

            // Byte-copy the packed wire layout.
            InputRecord records[records_per_tile];
            std::memcpy(records, words, sizeof(records));

            [[intel::initiation_interval(1)]]
            for (std::size_t record = 0; record < records_per_tile; ++record) {
                // Flag nonzero reserved data and forward every record.
                if (records[record].reserved != 0) errors |= 1u;
                InputRecords::write(records[record]);
            }
        }
        // PipelineFrame sends these accumulated flags only after all tasks have joined.
        return errors;
    }

    // P selects a modulus plane. Lanes select coefficient positions within a block.
    template <std::size_t P>
    inline void distribute_modulus(const InputRecord &record) {
        CoefficientBlock key{}, c1{};
        // Copy supplied secret-key and C1 residues as-is.
        #pragma unroll
        for (std::size_t lane = 0; lane < coefficient_lanes; ++lane) {
            key.lane[lane] = record.secret_key[P][lane];
            c1.lane[lane] = record.c1[P][lane];
        }
        // Key feeds its NTT, and C1 feeds polynomial arithmetic.
        ModulusPipes<P>::key::write(key);
        ModulusPipes<P>::c1::write(c1);
    }

    // Split each record into shared encoding/error and per-modulus key/C1 streams.
    [[intel::use_stall_enable_clusters]]
    inline void distribute_input_frame() {

        [[intel::initiation_interval(1)]]
        for (std::size_t block = 0; block < blocks_per_frame; ++block) {
            const InputRecord record = InputRecords::read();
            ComplexBlock encoding{};
            ErrorBlock error{};

            // Keep encoding values and signed error samples in their original lane order.
            #pragma unroll
            for (std::size_t lane = 0; lane < coefficient_lanes; ++lane) {
                encoding.lane[lane] = record.encoding[lane];
                error.lane[lane] = record.error[lane];
            }

            // Queue errors before encoding, preserving coefficient order. The
            // IFFT adapter pairs each error with the same ordinal valid output.
            IfftError::write(error);
            EncodingInput::write(encoding);
            distribute_modulus<0>(record);
            distribute_modulus<1>(record);
            distribute_modulus<2>(record);
            distribute_modulus<3>(record);
            distribute_modulus<4>(record);
            distribute_modulus<5>(record);
        }
    }

} // namespace ckks
