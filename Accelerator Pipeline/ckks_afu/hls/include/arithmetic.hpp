// Fixed-width modular arithmetic shared by scale/reduce and polynomial stages.
#pragma once

#include "parameters.hpp"

namespace ckks {
    // Arithmetic from the existing CKKS pipeline, with its operation order unchanged.
    // cr0/cr1 are the low/high words of floor(2^64 / mod_value).
    // The stored reciprocal and single correction assume 1 < mod_value < 2^31.
    // Require val > INT64_MIN so its signed negation is representable.
    inline uint32_t barrett_reduce_64_core(int64_t val, uint32_t mod_value, uint32_t cr0, uint32_t cr1)
    {
        // Reduce the magnitude first and remember whether to restore a minus sign.
        uint64_t coeff_abs = (val < 0) ? static_cast<uint64_t>(-val) : static_cast<uint64_t>(val);
        uint32_t sign_mask = static_cast<uint32_t>(val < 0);

        // Split the magnitude into words for a reciprocal multiply.
        uint32_t coeff_lo = static_cast<uint32_t>(coeff_abs);
        uint32_t coeff_hi = static_cast<uint32_t>(coeff_abs >> 32);

        // Partial products recover the quotient estimate.
        uint64_t tmp0 = static_cast<uint64_t>(coeff_lo) * cr0;
        uint64_t tmp1 = static_cast<uint64_t>(coeff_lo) * cr1;
        uint64_t tmp2 = static_cast<uint64_t>(coeff_hi) * cr0;

        // Accumulate the middle product word with explicit carry bits.
        uint32_t right_hw = static_cast<uint32_t>(tmp0 >> 32);
        uint32_t mid_lo = right_hw + static_cast<uint32_t>(tmp1);
        uint32_t mid_hi = static_cast<uint32_t>(tmp1 >> 32) + (mid_lo < right_hw);
        uint32_t mid2_lo = mid_lo + static_cast<uint32_t>(tmp2);
        uint32_t mid2_hi = static_cast<uint32_t>(tmp2 >> 32) + (mid2_lo < mid_lo);

        // Only the low 32 quotient bits are needed for this wrapped subtraction.
        uint32_t tmp = coeff_hi * cr1 + mid_hi + mid2_hi;
        tmp = coeff_lo - tmp * mod_value;

        // The reciprocal estimate leaves a remainder below 2*mod_value.
        if (tmp >= mod_value) tmp -= mod_value;

        // Restore the sign with masks. For negative multiples of mod_value,
        // tmp == 0 yields mod_value.
        uint32_t result = ((mod_value - tmp) & (-sign_mask)) + (tmp & (sign_mask - 1));

        return result;
    }

    // Unsigned-product variant with the same reciprocal and modulus bounds.
    // Returns a residue in [0, mod_value).
    inline uint32_t barrett_reduce_u64_core(uint64_t product, uint32_t mod_value, uint32_t cr0, uint32_t cr1)
    {
        uint32_t prod_lo = static_cast<uint32_t>(product);
        uint32_t prod_hi = static_cast<uint32_t>(product >> 32);

        // Multiply the input words by the split reciprocal.
        uint64_t tmp0 = static_cast<uint64_t>(prod_lo) * cr0;
        uint64_t tmp1 = static_cast<uint64_t>(prod_lo) * cr1;
        uint64_t tmp2 = static_cast<uint64_t>(prod_hi) * cr0;

        // Propagate carries into the low word of the high-half product.
        uint32_t right_hw = static_cast<uint32_t>(tmp0 >> 32);
        uint32_t mid_lo = right_hw + static_cast<uint32_t>(tmp1);
        uint32_t mid_hi = static_cast<uint32_t>(tmp1 >> 32) + (mid_lo < right_hw);
        uint32_t mid2_lo = mid_lo + static_cast<uint32_t>(tmp2);
        uint32_t mid2_hi = static_cast<uint32_t>(tmp2 >> 32) + (mid2_lo < mid_lo);

        // Subtract the approximate multiple in uint32_t arithmetic.
        uint32_t tmp = prod_hi * cr1 + mid_hi + mid2_hi;
        tmp = prod_lo - tmp * mod_value;

        // At most one extra modulus subtraction is needed under the bounds above.
        if (tmp >= mod_value) tmp -= mod_value;
        return tmp;
    }

    // Add reduced residues with one subtraction. Require a,b < mod_value
    // and 0 < mod_value < 2^31 so a+b fits in uint32_t.
    inline uint32_t mod_add(uint32_t a, uint32_t b, uint32_t mod_value)
    {
        uint32_t sum = a + b;
        // Expand the comparison to an all-ones or all-zero subtraction mask.
        int32_t is_ge_q = static_cast<int32_t>(sum >= mod_value);
        uint32_t mask = static_cast<uint32_t>(-is_ge_q);
        return sum - (mod_value & mask);
    }

    // Return -a mod mod_value for a reduced residue, preserving zero.
    inline uint32_t mod_neg(uint32_t a, uint32_t mod_value)
    {
        int32_t non_zero = static_cast<int32_t>(a != 0);
        uint32_t mask = static_cast<uint32_t>(-non_zero);
        return (mod_value - a) & mask;
    }

} // namespace ckks
