#pragma once

#include <cstdint>
#include <cstddef>

#include "sycl_ckks_accelerator/ckks_types.h"

namespace ckks {

constexpr size_t NUM_BLOCKS = POLY_N / LANES;
constexpr size_t PIPE_DEPTH_BUFFERED = NUM_BLOCKS;  // Pipes that must buffer a full polynomial
constexpr size_t PIPE_DEPTH_STREAMING = NUM_BLOCKS;

// Returns false for an unknown modulus.
inline bool get_barrett_constants(uint32_t mod_value, uint32_t& cr_lo, uint32_t& cr_hi)
{
    switch (mod_value) {
        case 134012929u:  cr_lo = 0x0c84dfe5u; cr_hi = 0x00000020u; return true;
        case 134111233u:  cr_lo = 0x06814e43u; cr_hi = 0x00000020u; return true;
        case 134176769u:  cr_lo = 0x02802e03u; cr_hi = 0x00000020u; return true;
        case 1053818881u: cr_lo = 0x135bf4bau; cr_hi = 0x00000004u; return true;
        case 1054015489u: cr_lo = 0x132a2218u; cr_hi = 0x00000004u; return true;
        case 1054212097u: cr_lo = 0x12f85437u; cr_hi = 0x00000004u; return true;
        case 1055260673u: cr_lo = 0x11ef051eu; cr_hi = 0x00000004u; return true;
        case 1056178177u: cr_lo = 0x11074e88u; cr_hi = 0x00000004u; return true;
        case 1056440321u: cr_lo = 0x10c52d4au; cr_hi = 0x00000004u; return true;
        case 1058209793u: cr_lo = 0x0f07a84au; cr_hi = 0x00000004u; return true;
        case 1060175873u: cr_lo = 0x0d1a6142u; cr_hi = 0x00000004u; return true;
        case 1060700161u: cr_lo = 0x0c9725e9u; cr_hi = 0x00000004u; return true;
        case 1060765697u: cr_lo = 0x0c86c0d4u; cr_hi = 0x00000004u; return true;
        case 1061093377u: cr_lo = 0x0c34cf30u; cr_hi = 0x00000004u; return true;
        case 1062469633u: cr_lo = 0x0add3267u; cr_hi = 0x00000004u; return true;
        case 1062535169u: cr_lo = 0x0accdb49u; cr_hi = 0x00000004u; return true;
        default: return false;
    }
}

inline uint32_t barrett_reduce_64_core(int64_t val, uint32_t mod_value, uint32_t cr0, uint32_t cr1,
    bool negate_result = false)
{
    uint64_t coeff_abs = (val < 0) ? static_cast<uint64_t>(-val) : static_cast<uint64_t>(val);
    uint32_t sign_mask = static_cast<uint32_t>(val < 0);

    uint32_t coeff_lo = static_cast<uint32_t>(coeff_abs);
    uint32_t coeff_hi = static_cast<uint32_t>(coeff_abs >> 32);

    uint64_t tmp0 = static_cast<uint64_t>(coeff_lo) * cr0;
    uint64_t tmp1 = static_cast<uint64_t>(coeff_lo) * cr1;
    uint64_t tmp2 = static_cast<uint64_t>(coeff_hi) * cr0;

    uint32_t right_hw = static_cast<uint32_t>(tmp0 >> 32);
    uint32_t mid_lo = right_hw + static_cast<uint32_t>(tmp1);
    uint32_t mid_hi = static_cast<uint32_t>(tmp1 >> 32) + (mid_lo < right_hw);
    uint32_t mid2_lo = mid_lo + static_cast<uint32_t>(tmp2);
    uint32_t mid2_hi = static_cast<uint32_t>(tmp2 >> 32) + (mid2_lo < mid_lo);

    uint32_t tmp = coeff_hi * cr1 + mid_hi + mid2_hi;
    tmp = coeff_lo - tmp * mod_value;

    if (tmp >= mod_value) tmp -= mod_value;

    uint32_t result = ((mod_value - tmp) & (-sign_mask)) + (tmp & (sign_mask - 1));

    if (negate_result) {
        uint32_t mask = static_cast<uint32_t>(-(result != 0));
        result = (mod_value - result) & mask;
    }

    return result;
}

inline uint32_t barrett_reduce_u64_core(uint64_t product, uint32_t mod_value, uint32_t cr0, uint32_t cr1)
{
    uint32_t prod_lo = static_cast<uint32_t>(product);
    uint32_t prod_hi = static_cast<uint32_t>(product >> 32);

    uint64_t tmp0 = static_cast<uint64_t>(prod_lo) * cr0;
    uint64_t tmp1 = static_cast<uint64_t>(prod_lo) * cr1;
    uint64_t tmp2 = static_cast<uint64_t>(prod_hi) * cr0;

    uint32_t right_hw = static_cast<uint32_t>(tmp0 >> 32);
    uint32_t mid_lo = right_hw + static_cast<uint32_t>(tmp1);
    uint32_t mid_hi = static_cast<uint32_t>(tmp1 >> 32) + (mid_lo < right_hw);
    uint32_t mid2_lo = mid_lo + static_cast<uint32_t>(tmp2);
    uint32_t mid2_hi = static_cast<uint32_t>(tmp2 >> 32) + (mid2_lo < mid_lo);

    uint32_t tmp = prod_hi * cr1 + mid_hi + mid2_hi;
    tmp = prod_lo - tmp * mod_value;

    if (tmp >= mod_value) tmp -= mod_value;
    return tmp;
}

inline uint32_t mod_add(uint32_t a, uint32_t b, uint32_t mod_value)
{
    uint32_t sum = a + b;
    int32_t is_ge_q = static_cast<int32_t>(sum >= mod_value);
    uint32_t mask = static_cast<uint32_t>(-is_ge_q);
    return sum - (mod_value & mask);
}

inline uint32_t mod_neg(uint32_t a, uint32_t mod_value)
{
    int32_t non_zero = static_cast<int32_t>(a != 0);
    uint32_t mask = static_cast<uint32_t>(-non_zero);
    return (mod_value - a) & mask;
}

} // namespace ckks
