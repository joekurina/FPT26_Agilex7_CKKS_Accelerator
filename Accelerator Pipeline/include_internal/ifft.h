#pragma once

#include "common.h"
#include "pipes.h"
#include "data_types.h"
#include "rtl/fhe_ifft_8k_4lanes_double_261_sycl.hpp"
#include <sycl/sycl.hpp>
#include <sycl/ext/intel/fpga_extensions.hpp>

namespace ckks {

class IFFTKernelTask;

class IFFTKernel {
public:
    IFFTKernel() {}

    void operator()(sycl::handler& h) const {
        h.single_task<IFFTKernelTask>([=]() [[intel::kernel_args_restrict]] {

#ifdef FPGA_EMULATOR
            ifft8k_base_DUT* rtl_instance = fhe_ifft_8k_4lanes_double_261_new_instance();
#endif

            // Feed the non-stallable RTL every cycle, including idle calls.
            // The full-frame raw pipe separates RTL output from fanout backpressure.
            // Never wait on these services. Finite drains and copy-out own completion.
            while (1) {
                bool input_valid = false;
                encoding_block block = SharedToIFFTPipe::read(input_valid);

                fhe_ifft_8k_4lanes_double_261_input_t hw_in;
                hw_in.port_v_in_s = input_valid;
                hw_in.port_data_in_0re = block.element0.real();
                hw_in.port_data_in_0im = block.element0.imag();
                hw_in.port_data_in_1re = block.element1.real();
                hw_in.port_data_in_1im = block.element1.imag();
                hw_in.port_data_in_2re = block.element2.real();
                hw_in.port_data_in_2im = block.element2.imag();
                hw_in.port_data_in_3re = block.element3.real();
                hw_in.port_data_in_3im = block.element3.imag();

#ifdef FPGA_EMULATOR
                fhe_ifft_8k_4lanes_double_261_output_t hw_out = fhe_ifft_8k_4lanes_double_261(rtl_instance, hw_in);
#else
                fhe_ifft_8k_4lanes_double_261_output_t hw_out = fhe_ifft_8k_4lanes_double_261(hw_in);
#endif

                if (hw_out.port_v_out_s == 1) {
                    encoding_block output_block;
                    output_block.element0 = complex_double(hw_out.port_data_out_0re, hw_out.port_data_out_0im);
                    output_block.element1 = complex_double(hw_out.port_data_out_1re, hw_out.port_data_out_1im);
                    output_block.element2 = complex_double(hw_out.port_data_out_2re, hw_out.port_data_out_2im);
                    output_block.element3 = complex_double(hw_out.port_data_out_3re, hw_out.port_data_out_3im);

                    // Buffer each RTL output block before the six-way fanout.
                    IFFTRawOutputPipe::write(output_block);
                }
            }
            // The emulator instance lives until process exit.
        });
    }
};

}
