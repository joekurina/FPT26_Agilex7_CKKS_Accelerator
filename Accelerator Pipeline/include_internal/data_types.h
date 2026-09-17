#pragma once

#include "common.h"
#include <cstdint>
#include <complex>

namespace ckks {

#ifndef CSL_PACKED
#ifdef _WIN32
#define CSL_PACKED(struct_def) __pragma(pack(push, 1)) struct_def __pragma(pack(pop))
#else
#define CSL_PACKED(struct_def) struct_def __attribute__((__packed__))
#endif
#endif

using complex_double = std::complex<double>;

CSL_PACKED(struct encoding_block {
    complex_double element0;
    complex_double element1;
    complex_double element2;
    complex_double element3;
});

CSL_PACKED(struct u32x4 {
    uint32_t element0;
    uint32_t element1;
    uint32_t element2;
    uint32_t element3;
});

CSL_PACKED(struct i8x4 {
    int8_t element0;
    int8_t element1;
    int8_t element2;
    int8_t element3;
});

CSL_PACKED(struct i64x4 {
    int64_t element0;
    int64_t element1;
    int64_t element2;
    int64_t element3;
});

struct PipelineInputBlock {
    encoding_block encoding;
    i8x4 error;
    u32x4 secret_key[NUM_MODULI];
    u32x4 c1[NUM_MODULI];
};

inline void pack_scalar_to_block(const uint32_t* src, size_t block_idx, u32x4& dst)
{
    size_t base = block_idx * LANES;
    dst.element0 = src[base + 0];
    dst.element1 = src[base + 1];
    dst.element2 = src[base + 2];
    dst.element3 = src[base + 3];
}

inline void pack_error_to_block(const int8_t* src, size_t block_idx, i8x4& dst)
{
    size_t base = block_idx * LANES;
    dst.element0 = src[base + 0];
    dst.element1 = src[base + 1];
    dst.element2 = src[base + 2];
    dst.element3 = src[base + 3];
}

inline void pack_encoding_to_block(const complex_double* src, size_t block_idx, encoding_block& dst)
{
    size_t base = block_idx * LANES;
    dst.element0 = src[base + 0];
    dst.element1 = src[base + 1];
    dst.element2 = src[base + 2];
    dst.element3 = src[base + 3];
}

} // namespace ckks
