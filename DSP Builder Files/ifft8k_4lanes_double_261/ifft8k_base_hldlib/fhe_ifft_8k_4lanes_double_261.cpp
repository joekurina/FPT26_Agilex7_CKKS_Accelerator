/**
 * High Level Design Compiler for Altera(R) FPGAs Version 26.1 (Release Build #805d06383c)
 * Software model created on 2026-08-25 13:21:30
 * Generation mode: Bit Accurate
 */
#ifndef CSL_USE_GMP
    #define CSL_USE_GMP
#endif
#ifndef NO_SYCL
#define CSL_EXTERNAL SYCL_EXTERNAL
#endif
#include "fhe_ifft_8k_4lanes_double_261_sycl.hpp"
#include "ifft8k_base_DUT.h"
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

extern "C" ifft8k_base_DUT* fhe_ifft_8k_4lanes_double_261_new_instance()
{
    uint8_t* instance_data = (uint8_t*)malloc(sizeof(ifft8k_base_DUT));
    ifft8k_base_DUT* instance = new (instance_data) ifft8k_base_DUT();
    instance->reset();
    return instance;
}

extern "C" void fhe_ifft_8k_4lanes_double_261_delete_instance(ifft8k_base_DUT* instance)
{
    instance->~ifft8k_base_DUT();
    free(instance);
}

extern "C" fhe_ifft_8k_4lanes_double_261_output_t fhe_ifft_8k_4lanes_double_261(ifft8k_base_DUT* instance, fhe_ifft_8k_4lanes_double_261_input_t input)
{
    assert(instance != nullptr && "Invalid emulator instance!");
    ifft8k_base_DUT::io_struct_ChannelIn input0 {};
    input0.port_v_in_s = input.port_v_in_s;
    input0.port_data_in_0re = input.port_data_in_0re;
    input0.port_data_in_0im = input.port_data_in_0im;
    input0.port_data_in_1re = input.port_data_in_1re;
    input0.port_data_in_1im = input.port_data_in_1im;
    input0.port_data_in_2re = input.port_data_in_2re;
    input0.port_data_in_2im = input.port_data_in_2im;
    input0.port_data_in_3re = input.port_data_in_3re;
    input0.port_data_in_3im = input.port_data_in_3im;
    instance->write(input0);

    ifft8k_base_DUT::io_struct_ChannelOut output0 {};
    instance->read(output0);

    fhe_ifft_8k_4lanes_double_261_output_t result;
    result.port_v_out_s = output0.port_v_out_s;
    result.port_data_out_0re = output0.port_data_out_0re;
    result.port_data_out_0im = output0.port_data_out_0im;
    result.port_data_out_1re = output0.port_data_out_1re;
    result.port_data_out_1im = output0.port_data_out_1im;
    result.port_data_out_2re = output0.port_data_out_2re;
    result.port_data_out_2im = output0.port_data_out_2im;
    result.port_data_out_3re = output0.port_data_out_3re;
    result.port_data_out_3im = output0.port_data_out_3im;
    return result;
}
