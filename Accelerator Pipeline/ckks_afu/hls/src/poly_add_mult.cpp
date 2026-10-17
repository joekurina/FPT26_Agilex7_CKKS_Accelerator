// Form each C0 modulus plane from the transformed secret key, message, and supplied C1.
#include "poly_add_mult.hpp"
#include "arithmetic.hpp"
#include "streaming_pipes.hpp"

namespace ckks {
    template <std::size_t P>

    [[intel::use_stall_enable_clusters]]
    void polynomial_frame() {
        constexpr Modulus modulus = moduli[P];

        [[intel::initiation_interval(1)]]
        for (std::size_t block = 0; block < blocks_per_frame; ++block) {
            const CoefficientBlock key = ModulusPipes<P>::key_ntt::read();
            const CoefficientBlock c1 = ModulusPipes<P>::c1::read();
            const CoefficientBlock message = ModulusPipes<P>::message_ntt::read();

            CoefficientBlock output{};

            #pragma unroll
            for (std::size_t lane = 0; lane < coefficient_lanes; ++lane) {
                // Widen before multiplication to retain the full unsigned product.
                const std::uint64_t product = static_cast<std::uint64_t>(key.lane[lane]) * c1.lane[lane];
                // Barrett Reduction
                const std::uint32_t reduced = barrett_reduce_u64_core(product, modulus.prime, modulus.barrett_low, modulus.barrett_high);
                // Negate the secret-key product, then add the noisy message modulo q_P.
                // mod_add expects reduced operands and a nonoverflowing uint32_t sum.
                output.lane[lane] = mod_add(mod_neg(reduced, modulus.prime), message.lane[lane], modulus.prime);
            }
            // Egress drains these C0 blocks into the corresponding modulus plane.
            ModulusPipes<P>::c0::write(output);
        }
    }

} // namespace ckks
