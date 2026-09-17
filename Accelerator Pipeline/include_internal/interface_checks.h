#pragma once

// Fixed ABI checks, included once by ckks_accelerator.cpp.
#include "data_types.h"
#include "rtl/fhe_ifft_8k_4lanes_double_261_sycl.hpp"
#include "rtl/the_nwc_8k_ntt_sycl.hpp"

namespace ckks {

// Packed lane types
static_assert(sizeof(encoding_block) == sizeof(complex_double) * 4, "encoding_block size mismatch");
static_assert(sizeof(u32x4) == sizeof(uint32_t) * 4, "u32x4 size mismatch");
static_assert(sizeof(i8x4) == sizeof(int8_t) * 4, "i8x4 size mismatch");
static_assert(sizeof(i64x4) == sizeof(int64_t) * 4, "i64x4 size mismatch");

// Ingress DMA layout
static_assert(sizeof(encoding_block) == 64 && sizeof(i8x4) == 4 && sizeof(u32x4) == 16);
static_assert(sizeof(PipelineInputBlock) == 264, "retain the existing DMA ABI");

// Imported IFFT ABI
static_assert(sizeof(fhe_ifft_8k_4lanes_double_261_input_t) == 65,
              "unexpected fhe_ifft_8k input ABI size");
static_assert(sizeof(fhe_ifft_8k_4lanes_double_261_output_t) == 65,
              "unexpected fhe_ifft_8k output ABI size");

// Imported NTT ABI
static_assert(sizeof(the_nwc_8k_ntt_input_t) == 34,
              "unexpected the_nwc_8k_ntt input ABI size");
static_assert(sizeof(the_nwc_8k_ntt_output_t) == 34,
              "unexpected the_nwc_8k_ntt output ABI size");

} // namespace ckks
