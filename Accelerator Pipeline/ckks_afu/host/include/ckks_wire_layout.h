// Fixed frame extents shared by the serializer, native host and HLS interfaces.

#ifndef CKKS_WIRE_LAYOUT_H
#define CKKS_WIRE_LAYOUT_H

#include <stddef.h>
#include <stdint.h>

/* Constants used by the current frame format and device interface. */
// Input bytes cover packed four-lane records, including C1. Output bytes cover
// C0 planes only.
#ifdef __cplusplus
inline constexpr uint32_t CKKS_NATIVE_ABI_VERSION = 1;
inline constexpr size_t CKKS_NATIVE_POLY_N = 8192;
inline constexpr size_t CKKS_NATIVE_NUM_MODULI = 6;
inline constexpr size_t CKKS_NATIVE_LANES = 4;
inline constexpr size_t CKKS_NATIVE_BLOCKS_PER_FRAME = 2048;
inline constexpr uint32_t CKKS_NATIVE_INPUT_BYTES = 540672;
inline constexpr uint32_t CKKS_NATIVE_C0_BYTES = 196608;

#else
// Keep the C enum values identical to the typed C++ constants above.
enum ckks_native_wire_constant {
    CKKS_NATIVE_ABI_VERSION = 1,
    CKKS_NATIVE_POLY_N = 8192,
    CKKS_NATIVE_NUM_MODULI = 6,
    CKKS_NATIVE_LANES = 4,
    CKKS_NATIVE_BLOCKS_PER_FRAME = 2048,
    CKKS_NATIVE_INPUT_BYTES = 540672,
    CKKS_NATIVE_C0_BYTES = 196608,
};
#endif

#endif
