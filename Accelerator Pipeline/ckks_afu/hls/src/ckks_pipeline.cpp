#include "ckks_pipeline.hpp"
#include "ingress.hpp"
#include "egress.hpp"
#include <sycl/ext/altera/experimental/task_sequence.hpp>

namespace ckks {
// P selects one parallel modulus limb. The shared IFFT supplies all six moduli limbs.
template <std::size_t P>
[[intel::use_stall_enable_clusters]]
void modulus_frame() {
    // Message-input reduction is part of the message NTT task. Common scaling,
    // rounding and error addition run at the IFFT output before fan-out.
    // Polynomial arithmetic consumes both transformed streams and the supplied C1.
    altera::task_sequence<ntt_frame<P, NttRole::key>> key_ntt;
    altera::task_sequence<ntt_frame<P, NttRole::message>> message_ntt;
    altera::task_sequence<polynomial_frame<P>> polynomial;

    // Start all producers and consumers before joining any of these tasks.
    key_ntt.async();
    message_ntt.async();
    polynomial.async();

    // Each get waits for the corresponding single-frame invocation to finish.
    key_ntt.get();
    message_ntt.get();
    polynomial.get();
}

// Fixed loop counts in the stages define this invocation's frame boundaries.
inline void PipelineFrame::operator()() const {
    // Shared parsing, distribution, and IFFT tasks supply the parallel modulus limbs.
    altera::task_sequence<parse_input_frame> parser;
    altera::task_sequence<distribute_input_frame> ingress;
    altera::task_sequence<ifft_frame> ifft;
    altera::task_sequence<fanout_ifft_frame_blocking> fanout;
    altera::task_sequence<packetize_output_frame> output;

    // These explicit instances match the six entries in moduli and ModulusPipes.
    altera::task_sequence<modulus_frame<0>> p0;
    altera::task_sequence<modulus_frame<1>> p1;
    altera::task_sequence<modulus_frame<2>> p2;
    altera::task_sequence<modulus_frame<3>> p3;
    altera::task_sequence<modulus_frame<4>> p4;
    altera::task_sequence<modulus_frame<5>> p5;

    // Start every communicating task before waiting for any task to finish.
    parser.async();
    ingress.async();
    ifft.async();
    fanout.async();
    p0.async();
    p1.async();
    p2.async();
    p3.async();
    p4.async();
    p5.async();
    output.async();

    // Only the parser returns error bits.
    auto errors = parser.get();
    ingress.get();
    ifft.get();
    fanout.get();
    p0.get();
    p1.get();
    p2.get();
    p3.get();
    p4.get();
    p5.get();
    output.get();

    // Publish reserved-field flags after all stages finish, in one transfer with TLAST.
    StatusOutput::write(StatusBeat(FrameStatus{errors}, true));
}
} // namespace ckks

// This entry point submits the pipeline for AHLS IP generation.
// The deployed host is a separate project C++ program using OPAE.
int main() {
    sycl::queue queue(sycl::ext::altera::fpga_selector_v);
    queue.single_task<ckks::PipelineKernel>(ckks::PipelineFrame{});
    return 0;
}
