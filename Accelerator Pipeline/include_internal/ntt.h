#pragma once

#include "common.h"
#include "pipes.h"
#include "data_types.h"
#include "rtl/the_nwc_8k_ntt_sycl.hpp"
#include <sycl/sycl.hpp>
#include <sycl/ext/intel/fpga_extensions.hpp>

namespace ckks {

inline void pack_ntt_coefficient(uint32_t port[2], uint32_t value)
{
    port[0] = value;
    port[1] = 0;
}

inline uint32_t unpack_ntt_coefficient(const uint32_t port[2])
{
    // Reduced coefficients fit in the low word of each 64-bit RTL lane.
    return port[0];
}

struct NTT_A_Tag {};
struct NTT_B_Tag {};

template <int P, typename Tag>
struct NTTPipeTraits;

template <int P>
struct NTTPipeTraits<P, NTT_A_Tag> {
    using InputPipe = typename PipeSet<P>::EntryToNTTAPipe;
    using DownstreamPipe = typename PipeSet<P>::NTTAToPolyMultNegPipe;
};

template <int P>
struct NTTPipeTraits<P, NTT_B_Tag> {
    using InputPipe = typename PipeSet<P>::ScaleReduceToNTTBPipe;
    using DownstreamPipe = typename PipeSet<P>::NTTBToPolyAddPipe;
};

template<int P, typename Tag> class NTTServiceTask;

template<int P, typename Tag>
class NTTService {
public:
    explicit NTTService(uint8_t selector) : selector_(selector) {}
    void operator()(sycl::handler &h) const {
        const uint8_t selector = selector_;
        h.single_task<NTTServiceTask<P, Tag>>([=]() {
            using Traits = NTTPipeTraits<P, Tag>;
#ifdef FPGA_EMULATOR
            reg_test_verifyNTT_multi_DUT *instance = the_nwc_8k_ntt_new_instance();
#endif
            // Persistent RTL service. No completion event is awaited.
            while (true) {
#ifdef FPGA_EMULATOR
                // The C model needs idle calls to drain output after the input frame.
                // Hardware retains the imported RTL blocking-read contract.
                bool valid = false;
                const u32x4 candidate = Traits::InputPipe::read(valid);
                const u32x4 input = valid ? candidate : u32x4{};
#else
                const u32x4 input = Traits::InputPipe::read();
                const bool valid = true;
#endif
                the_nwc_8k_ntt_input_t in{};
                in.port_in_v_s = valid;
                in.port_in_c_s = static_cast<int8_t>(selector);
                pack_ntt_coefficient(in.port_x_in_0, input.element0);
                pack_ntt_coefficient(in.port_x_in_1, input.element1);
                pack_ntt_coefficient(in.port_x_in_2, input.element2);
                pack_ntt_coefficient(in.port_x_in_3, input.element3);
#ifdef FPGA_EMULATOR
                const auto out = the_nwc_8k_ntt(instance, in);
#else
                const auto out = the_nwc_8k_ntt(in);
#endif
                if (out.port_out_v_s != 0) {
                    const u32x4 result{
                        unpack_ntt_coefficient(out.port_out_q_0),
                        unpack_ntt_coefficient(out.port_out_q_1),
                        unpack_ntt_coefficient(out.port_out_q_2),
                        unpack_ntt_coefficient(out.port_out_q_3)};
                    Traits::DownstreamPipe::write(result);
                }
            }
        });
    }
private:
    uint8_t selector_;
};
} // namespace ckks
