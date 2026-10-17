#include "ifft.hpp"
#include "streaming_pipes.hpp"
#include "fhe_ifft_8k_4lanes_double_261_sycl.hpp"

namespace ckks {
// Scale, round, convert to signed integers and add the error
inline void write_ifft_result(
    const fhe_ifft_8k_4lanes_double_261_output_t &result,
    const ErrorBlock &error) {
    const double real[coefficient_lanes] = {
        result.port_data_out_0re, result.port_data_out_1re,
        result.port_data_out_2re, result.port_data_out_3re
    };
    SignedCoefficientBlock output{};

    #pragma unroll
    for (std::size_t lane = 0; lane < coefficient_lanes; ++lane) {
        const double rounded = sycl::round(real[lane] * coefficient_scale);
        // Preserve the same finite/range and signed-sum preconditions.
        output.lane[lane] = static_cast<std::int64_t>(rounded) + error.lane[lane];
    }

    IfftOutput::write(output);
}

// Pair each input with one error block and convert the corresponding IFFT return.
[[intel::use_stall_enable_clusters]]
inline void ifft_frame() {
    [[intel::initiation_interval(1)]]
    for (std::size_t block = 0; block < blocks_per_frame; ++block) {
        const ComplexBlock input = EncodingInput::read();

        // Ingress offers error j before encoding j. Keep this value local to
        // iteration j.
        const ErrorBlock error = IfftError::read();
        fhe_ifft_8k_4lanes_double_261_input_t request{};
        request.port_v_in_s = 1;
        request.port_data_in_0re = input.lane[0].real;
        request.port_data_in_0im = input.lane[0].imag;
        request.port_data_in_1re = input.lane[1].real;
        request.port_data_in_1im = input.lane[1].imag;
        request.port_data_in_2re = input.lane[2].real;
        request.port_data_in_2im = input.lane[2].imag;
        request.port_data_in_3re = input.lane[3].real;
        request.port_data_in_3im = input.lane[3].imag;
        const auto response = fhe_ifft_8k_4lanes_double_261(request);

        // The hardware contract pairs call/response ordinals.
        // AHLS must retain every live error until return.
        if (response.port_v_out_s == 1) {
            write_ifft_result(response, error);
        }
    }
}

// Broadcast the shared signed message directly to the message-role NTTs.
[[intel::use_stall_enable_clusters]]
inline void fanout_ifft_frame_blocking() {
    [[intel::initiation_interval(1)]]
    for (std::size_t block = 0; block < blocks_per_frame; ++block) {
        const SignedCoefficientBlock output = IfftOutput::read();
        // Each P receives identical integers in the same block and lane order.
        ModulusPipes<0>::message::write(output);
        ModulusPipes<1>::message::write(output);
        ModulusPipes<2>::message::write(output);
        ModulusPipes<3>::message::write(output);
        ModulusPipes<4>::message::write(output);
        ModulusPipes<5>::message::write(output);
    }
}

} // namespace ckks
