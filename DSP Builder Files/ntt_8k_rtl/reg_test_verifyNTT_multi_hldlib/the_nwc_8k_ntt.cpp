/**
 * High Level Design Compiler for Altera(R) FPGAs Version 2026.3 (Release Build #847757300c)
 * Software model created on 2026-08-26 10:03:58
 * Generation mode: Bit Accurate
 */
#ifndef CSL_USE_GMP
    #define CSL_USE_GMP
#endif
#ifndef NO_SYCL
#define CSL_EXTERNAL SYCL_EXTERNAL
#endif
#include "the_nwc_8k_ntt_sycl.hpp"
#include "reg_test_verifyNTT_multi_DUT.h"
#include <stdio.h>
#include <assert.h>

namespace csl
{
#ifdef WRITE_STM_FILES
[[noreturn]] void fatal(const char* msg) { printf("Fatal error: %s\n", msg); exit(1); }
void error(const char* msg)              { printf("Error: %s\n", msg); }
void info(const char* msg)               { printf("Info: %s\n",  msg); }
#else
[[noreturn]] void fatal(const char* msg) { exit(1); }
void warning(const char* msg)            { }
void info(const char* msg)               { }
#endif
}

extern "C" reg_test_verifyNTT_multi_DUT* the_nwc_8k_ntt_new_instance()
{
    uint8_t* instance_data = (uint8_t*)malloc(sizeof(reg_test_verifyNTT_multi_DUT));
    reg_test_verifyNTT_multi_DUT* instance = new (instance_data) reg_test_verifyNTT_multi_DUT();
    instance->reset();
    return instance;
}

extern "C" void the_nwc_8k_ntt_delete_instance(reg_test_verifyNTT_multi_DUT* instance)
{
    instance->~reg_test_verifyNTT_multi_DUT();
    free(instance);
}

extern "C" the_nwc_8k_ntt_output_t the_nwc_8k_ntt(reg_test_verifyNTT_multi_DUT* instance, the_nwc_8k_ntt_input_t input)
{
    assert(instance != nullptr && "Invalid emulator instance!");
    reg_test_verifyNTT_multi_DUT::io_struct_ChannelIn input0 {};
    input0.In_V = input.port_in_v_s;
    input0.In_C = input.port_in_c_s;
    input0.X_in[0].set_from_uint_array(input.port_x_in_0, 2, 64, instance->get_temp_allocator());
    input0.X_in[1].set_from_uint_array(input.port_x_in_1, 2, 64, instance->get_temp_allocator());
    input0.X_in[2].set_from_uint_array(input.port_x_in_2, 2, 64, instance->get_temp_allocator());
    input0.X_in[3].set_from_uint_array(input.port_x_in_3, 2, 64, instance->get_temp_allocator());
    instance->write(input0);

    reg_test_verifyNTT_multi_DUT::io_struct_ChannelOut output0 {};
    instance->read(output0);

    the_nwc_8k_ntt_output_t result;
    result.port_out_v_s = output0.Out_V;
    result.port_out_c_s = output0.Out_C;
    output0.Out_Q[0].get_as_uint_array(result.port_out_q_0, 2, instance->get_temp_allocator());
    output0.Out_Q[1].get_as_uint_array(result.port_out_q_1, 2, instance->get_temp_allocator());
    output0.Out_Q[2].get_as_uint_array(result.port_out_q_2, 2, instance->get_temp_allocator());
    output0.Out_Q[3].get_as_uint_array(result.port_out_q_3, 2, instance->get_temp_allocator());
    return result;
}
