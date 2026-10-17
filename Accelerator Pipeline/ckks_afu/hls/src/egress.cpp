#include "egress.hpp"
#include "streaming_pipes.hpp"

namespace ckks {
    // Drain one complete modulus plane.
    template <std::size_t P>
    inline void write_c0_plane() {
        // A ResultWord holds four blocks. The frame block count must be divisible by four.
        for (std::size_t word = 0; word < blocks_per_frame / 4; ++word) {
            ResultWord output{};
            // Preserve block order and the coefficient-lane order within each block.
            for (auto &block : output.block) block = ModulusPipes<P>::c0::read();
            // TLAST belongs only to the final word of the final modulus plane.
            const bool last = P + 1 == modulus_count && word + 1 == blocks_per_frame / 4;
            DmaOutput::write(DmaOutputBeat(output, last));
        }
    }

    // Emit C0 planes P=0 through P=5 in order.
    [[intel::use_stall_enable_clusters]]
    inline void packetize_output_frame() {
        write_c0_plane<0>();
        write_c0_plane<1>();
        write_c0_plane<2>();
        write_c0_plane<3>();
        write_c0_plane<4>();
        write_c0_plane<5>();
    }
} // namespace ckks
