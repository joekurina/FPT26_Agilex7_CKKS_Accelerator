/**
 * High Level Design Compiler for Altera(R) FPGAs Version 2026.3 (Release Build #847757300c)
 * Software model created on 2026-08-26 10:03:58
 * Generation mode: Bit Accurate
 */
#include "the_nwc_8k_ntt_sycl.hpp"
#include "support/csl.h"
#include "support/csl_io.h"

class reg_test_verifyNTT_multi_DUTWrapperATB
{
public:
    void read_from_stm_ChannelIn(csl::stimulus_file& stm, the_nwc_8k_ntt_input_t& value_out)
    {
        int8_t tmp_value_outport_in_v_s;
        stm.get(tmp_value_outport_in_v_s, 1);
        value_out.port_in_v_s = tmp_value_outport_in_v_s;
        int8_t tmp_value_outport_in_c_s;
        stm.get(tmp_value_outport_in_c_s, 8);
        value_out.port_in_c_s = tmp_value_outport_in_c_s;
        uint32_t tmp_value_outport_x_in_0[2];
        stm.get(tmp_value_outport_x_in_0, 64, 2);
        for (size_t i = 0; i < 2; ++i)
        {
            value_out.port_x_in_0[i] = tmp_value_outport_x_in_0[i];
        }
        uint32_t tmp_value_outport_x_in_1[2];
        stm.get(tmp_value_outport_x_in_1, 64, 2);
        for (size_t i = 0; i < 2; ++i)
        {
            value_out.port_x_in_1[i] = tmp_value_outport_x_in_1[i];
        }
        uint32_t tmp_value_outport_x_in_2[2];
        stm.get(tmp_value_outport_x_in_2, 64, 2);
        for (size_t i = 0; i < 2; ++i)
        {
            value_out.port_x_in_2[i] = tmp_value_outport_x_in_2[i];
        }
        uint32_t tmp_value_outport_x_in_3[2];
        stm.get(tmp_value_outport_x_in_3, 64, 2);
        for (size_t i = 0; i < 2; ++i)
        {
            value_out.port_x_in_3[i] = tmp_value_outport_x_in_3[i];
        }
    }

    void read_from_stm_ChannelOut(csl::stimulus_file& stm, the_nwc_8k_ntt_output_t& value_out)
    {
        int8_t tmp_value_outport_out_v_s;
        stm.get(tmp_value_outport_out_v_s, 1);
        value_out.port_out_v_s = tmp_value_outport_out_v_s;
        int8_t tmp_value_outport_out_c_s;
        stm.get(tmp_value_outport_out_c_s, 8);
        value_out.port_out_c_s = tmp_value_outport_out_c_s;
        uint32_t tmp_value_outport_out_q_0[2];
        stm.get(tmp_value_outport_out_q_0, 64, 2);
        for (size_t i = 0; i < 2; ++i)
        {
            value_out.port_out_q_0[i] = tmp_value_outport_out_q_0[i];
        }
        uint32_t tmp_value_outport_out_q_1[2];
        stm.get(tmp_value_outport_out_q_1, 64, 2);
        for (size_t i = 0; i < 2; ++i)
        {
            value_out.port_out_q_1[i] = tmp_value_outport_out_q_1[i];
        }
        uint32_t tmp_value_outport_out_q_2[2];
        stm.get(tmp_value_outport_out_q_2, 64, 2);
        for (size_t i = 0; i < 2; ++i)
        {
            value_out.port_out_q_2[i] = tmp_value_outport_out_q_2[i];
        }
        uint32_t tmp_value_outport_out_q_3[2];
        stm.get(tmp_value_outport_out_q_3, 64, 2);
        for (size_t i = 0; i < 2; ++i)
        {
            value_out.port_out_q_3[i] = tmp_value_outport_out_q_3[i];
        }
    }

    bool run()
    {
        bool all_inputs_opened = true;
        reg_test_verifyNTT_multi_DUT* instance = the_nwc_8k_ntt_new_instance();
        instance->open_stimulus_files();
        the_nwc_8k_ntt_input_t input;
        the_nwc_8k_ntt_output_t output;
        csl::info("[reg_test_verifyNTT_multi_DUT] Opening stimulus files...");
        csl::stimulus_file io_struct_ChannelIn_stm_in0("../reg_test_verifyNTT_multi_DUT_ChannelIn_vunroll_x.stm", csl::stimulus_format::SIGNED);
        all_inputs_opened &= io_struct_ChannelIn_stm_in0.is_open();
        if (all_inputs_opened)
        {
            csl::info("[reg_test_verifyNTT_multi_DUT] Simulating...");
            while(io_struct_ChannelIn_stm_in0.next_line())
            {
                read_from_stm_ChannelIn(io_struct_ChannelIn_stm_in0, input);
                output = the_nwc_8k_ntt(instance, input);
            }
        }
        the_nwc_8k_ntt_delete_instance(instance);
        if (all_inputs_opened)
        {
            csl::info("[reg_test_verifyNTT_multi_DUT] Simulation has completed.");
            return true;
        }
        csl::error("[reg_test_verifyNTT_multi_DUT] Simulation failure! Stimulus file IO errors occurred.");
        return false;
    }

    bool compare()
    {
        bool success = true;
        success &= csl::compare_stm_files("reg_test_verifyNTT_multi_DUT_ChannelOut_vunroll_x.stm", "../reg_test_verifyNTT_multi_DUT_ChannelOut_vunroll_x.stm");
        if (success)
        {
            csl::info("[reg_test_verifyNTT_multi_DUT] Success! Software model matches Simulink simulation.");
        }
        else
        {
            csl::error("[reg_test_verifyNTT_multi_DUT] Error! Software model does not match Simulink simulation.");
        }
        return success;
    }
};


int main(int argc, char** argv)
{
    reg_test_verifyNTT_multi_DUTWrapperATB wrapper_atb;
    bool success = true;
    success = wrapper_atb.run();
    success = success && wrapper_atb.compare();
    return success ? 0 : 1;
}
