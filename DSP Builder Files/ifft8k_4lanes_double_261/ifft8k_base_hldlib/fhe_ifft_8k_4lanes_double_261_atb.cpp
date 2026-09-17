/**
 * High Level Design Compiler for Altera(R) FPGAs Version 26.1 (Release Build #805d06383c)
 * Software model created on 2026-08-25 13:21:30
 * Generation mode: Bit Accurate
 */
#include "fhe_ifft_8k_4lanes_double_261_sycl.hpp"
#include "support/csl.h"
#include "support/csl_io.h"

class ifft8k_base_DUTWrapperATB
{
public:
    void read_from_stm_ChannelIn(csl::stimulus_file& stm, fhe_ifft_8k_4lanes_double_261_input_t& value_out)
    {
        int8_t tmp_value_outport_v_in_s;
        stm.get(tmp_value_outport_v_in_s, 1);
        value_out.port_v_in_s = tmp_value_outport_v_in_s;
        stm.skip(1);
        double tmp_value_outport_data_in_0re;
        stm.get(tmp_value_outport_data_in_0re);
        value_out.port_data_in_0re = tmp_value_outport_data_in_0re;
        double tmp_value_outport_data_in_0im;
        stm.get(tmp_value_outport_data_in_0im);
        value_out.port_data_in_0im = tmp_value_outport_data_in_0im;
        double tmp_value_outport_data_in_1re;
        stm.get(tmp_value_outport_data_in_1re);
        value_out.port_data_in_1re = tmp_value_outport_data_in_1re;
        double tmp_value_outport_data_in_1im;
        stm.get(tmp_value_outport_data_in_1im);
        value_out.port_data_in_1im = tmp_value_outport_data_in_1im;
        double tmp_value_outport_data_in_2re;
        stm.get(tmp_value_outport_data_in_2re);
        value_out.port_data_in_2re = tmp_value_outport_data_in_2re;
        double tmp_value_outport_data_in_2im;
        stm.get(tmp_value_outport_data_in_2im);
        value_out.port_data_in_2im = tmp_value_outport_data_in_2im;
        double tmp_value_outport_data_in_3re;
        stm.get(tmp_value_outport_data_in_3re);
        value_out.port_data_in_3re = tmp_value_outport_data_in_3re;
        double tmp_value_outport_data_in_3im;
        stm.get(tmp_value_outport_data_in_3im);
        value_out.port_data_in_3im = tmp_value_outport_data_in_3im;
    }

    void read_from_stm_ChannelOut(csl::stimulus_file& stm, fhe_ifft_8k_4lanes_double_261_output_t& value_out)
    {
        int8_t tmp_value_outport_v_out_s;
        stm.get(tmp_value_outport_v_out_s, 1);
        value_out.port_v_out_s = tmp_value_outport_v_out_s;
        stm.skip(1);
        double tmp_value_outport_data_out_0re;
        stm.get(tmp_value_outport_data_out_0re);
        value_out.port_data_out_0re = tmp_value_outport_data_out_0re;
        double tmp_value_outport_data_out_0im;
        stm.get(tmp_value_outport_data_out_0im);
        value_out.port_data_out_0im = tmp_value_outport_data_out_0im;
        double tmp_value_outport_data_out_1re;
        stm.get(tmp_value_outport_data_out_1re);
        value_out.port_data_out_1re = tmp_value_outport_data_out_1re;
        double tmp_value_outport_data_out_1im;
        stm.get(tmp_value_outport_data_out_1im);
        value_out.port_data_out_1im = tmp_value_outport_data_out_1im;
        double tmp_value_outport_data_out_2re;
        stm.get(tmp_value_outport_data_out_2re);
        value_out.port_data_out_2re = tmp_value_outport_data_out_2re;
        double tmp_value_outport_data_out_2im;
        stm.get(tmp_value_outport_data_out_2im);
        value_out.port_data_out_2im = tmp_value_outport_data_out_2im;
        double tmp_value_outport_data_out_3re;
        stm.get(tmp_value_outport_data_out_3re);
        value_out.port_data_out_3re = tmp_value_outport_data_out_3re;
        double tmp_value_outport_data_out_3im;
        stm.get(tmp_value_outport_data_out_3im);
        value_out.port_data_out_3im = tmp_value_outport_data_out_3im;
    }

    bool run()
    {
        bool all_inputs_opened = true;
        ifft8k_base_DUT* instance = fhe_ifft_8k_4lanes_double_261_new_instance();
        instance->open_stimulus_files();
        fhe_ifft_8k_4lanes_double_261_input_t input;
        fhe_ifft_8k_4lanes_double_261_output_t output;
        csl::info("[ifft8k_base_DUT] Opening stimulus files...");
        csl::stimulus_file io_struct_ChannelIn_stm_in0("../ifft8k_base_DUT_ChannelIn_vunroll_cunroll_x.stm", csl::stimulus_format::SIGNED);
        all_inputs_opened &= io_struct_ChannelIn_stm_in0.is_open();
        if (all_inputs_opened)
        {
            csl::info("[ifft8k_base_DUT] Simulating...");
            while(io_struct_ChannelIn_stm_in0.next_line())
            {
                read_from_stm_ChannelIn(io_struct_ChannelIn_stm_in0, input);
                output = fhe_ifft_8k_4lanes_double_261(instance, input);
            }
        }
        fhe_ifft_8k_4lanes_double_261_delete_instance(instance);
        if (all_inputs_opened)
        {
            csl::info("[ifft8k_base_DUT] Simulation has completed.");
            return true;
        }
        csl::error("[ifft8k_base_DUT] Simulation failure! Stimulus file IO errors occurred.");
        return false;
    }

    bool compare()
    {
        bool success = true;
        success &= csl::compare_stm_files("ifft8k_base_DUT_ChannelOut_vunroll_cunroll_x.stm", "../ifft8k_base_DUT_ChannelOut_vunroll_cunroll_x.stm");
        if (success)
        {
            csl::info("[ifft8k_base_DUT] Success! Software model matches Simulink simulation.");
        }
        else
        {
            csl::error("[ifft8k_base_DUT] Error! Software model does not match Simulink simulation.");
        }
        return success;
    }
};


int main(int argc, char** argv)
{
    ifft8k_base_DUTWrapperATB wrapper_atb;
    bool success = true;
    success = wrapper_atb.run();
    success = success && wrapper_atb.compare();
    return success ? 0 : 1;
}
