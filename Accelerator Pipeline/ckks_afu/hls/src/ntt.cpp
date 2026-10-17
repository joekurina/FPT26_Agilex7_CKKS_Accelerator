#include "ntt.hpp"
#include "arithmetic.hpp"
#include "streaming_pipes.hpp"
#include "the_nwc_8k_ntt_sycl.hpp"

namespace ckks {
template <std::size_t P, NttRole Role>
inline void write_ntt_result(const the_nwc_8k_ntt_output_t &result) {
    CoefficientBlock output{};
    output.lane[0] = result.port_out_q_0[0];
    output.lane[1] = result.port_out_q_1[0];
    output.lane[2] = result.port_out_q_2[0];
    output.lane[3] = result.port_out_q_3[0];

    // Preserve the generated output lane order for polynomial_frame<P>.
    if constexpr (Role == NttRole::key) ModulusPipes<P>::key_ntt::write(output);
    else ModulusPipes<P>::message_ntt::write(output);
}

// Emit each completed imported return through the role-specific blocking pipe.
template <std::size_t P, NttRole Role>
[[intel::use_stall_enable_clusters]]
void ntt_frame() {
    [[intel::initiation_interval(1)]]
    for (std::size_t block = 0; block < blocks_per_frame; ++block) {
        CoefficientBlock input{};
        if constexpr (Role == NttRole::key) input = ModulusPipes<P>::key::read();
        else {
            // IFFT output already performed scale, round, int64 conversion and
            // error addition. Reduce that signed value for this NTT's modulus.
            const SignedCoefficientBlock message = ModulusPipes<P>::message::read();
            constexpr Modulus modulus = moduli[P];

            // Perform a modular reduction on the scaled plaintext + error message
            #pragma unroll
            for (std::size_t lane = 0; lane < coefficient_lanes; ++lane) {
                input.lane[lane] = barrett_reduce_64_core(message.lane[lane], modulus.prime, modulus.barrett_low, modulus.barrett_high);
            }
        }

        // Zero-initialization leaves element [1] of each generated input lane at zero.
        the_nwc_8k_ntt_input_t request{};

        // Mark the block valid and pass P as the modulus selector.
        request.port_in_v_s = 1;
        request.port_in_c_s = P;
        request.port_x_in_0[0] = input.lane[0];
        request.port_x_in_1[0] = input.lane[1];
        request.port_x_in_2[0] = input.lane[2];
        request.port_x_in_3[0] = input.lane[3];
        const auto response = the_nwc_8k_ntt(request);

        // The import transaction handshake owns completion and backpressure.
        write_ntt_result<P, Role>(response);
    }
}

} // namespace ckks
