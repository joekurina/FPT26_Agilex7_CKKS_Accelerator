// C-compatible host frame types and CPU serialization API shared with pipeline ingress.

#ifndef CKKS_NATIVE_H
#define CKKS_NATIVE_H

#include <stddef.h>
#include <stdint.h>
#include "ckks_wire_layout.h"

#ifdef __cplusplus
extern "C" {
#endif

/* CPU serialization results. */
// Any failure is returned.
typedef enum ckks_native_wire_result {
    CKKS_NATIVE_WIRE_OK = 0,
    CKKS_NATIVE_WIRE_INVALID_ARGUMENT = 1,
    CKKS_NATIVE_WIRE_BAD_LENGTH = 2,
    CKKS_NATIVE_WIRE_NONFINITE_ENCODING = 4,
    CKKS_NATIVE_WIRE_OVERLAPPING_MEMORY = 5,
    CKKS_NATIVE_WIRE_ADDRESS_RANGE = 6
} ckks_native_wire_result;

/* Host-side coefficient arrays. The serializer groups them into input records. */
typedef struct ckks_native_complex64 {
    double real;
    double imag;
} ckks_native_complex64;

// Logical arrays use coefficient indices within each modulus plane where present.
// Callers supply transform ordering and domains.
typedef struct ckks_native_input_frame {
    ckks_native_complex64 encoding[CKKS_NATIVE_POLY_N];
    int8_t error[CKKS_NATIVE_POLY_N];
    uint32_t secret_key[CKKS_NATIVE_NUM_MODULI][CKKS_NATIVE_POLY_N];
    uint32_t c1[CKKS_NATIVE_NUM_MODULI][CKKS_NATIVE_POLY_N];
} ckks_native_input_frame;

// Raw C0 output planes only. C1 is retained separately by the benchmark for assembly.
typedef struct ckks_native_c0_frame {
    uint32_t coefficients[CKKS_NATIVE_NUM_MODULI][CKKS_NATIVE_POLY_N];
} ckks_native_c0_frame;

// One wire record groups four consecutive indices. Packing fixes field offsets,
// while wire.cpp separately converts multi-byte fields to little-endian order.
#pragma pack(push, 1)
typedef struct ckks_native_input_record {
    ckks_native_complex64 encoding[CKKS_NATIVE_LANES];
    int8_t error[CKKS_NATIVE_LANES];
    uint32_t secret_key[CKKS_NATIVE_NUM_MODULI][CKKS_NATIVE_LANES];
    uint32_t c1[CKKS_NATIVE_NUM_MODULI][CKKS_NATIVE_LANES];
    // The encoder writes zero. HLS reports a nonzero field in parser status bit 0.
    uint32_t reserved;
} ckks_native_input_record;

#pragma pack(pop)

/* All wire lengths must match exactly. Caller supplies accessible, nonoverlapping
 * objects/buffers. Rejection leaves the destination unchanged. Serialization
 * preserves binary64 bits, signed error bytes and uint32 residues.
 * Callers handle arithmetic-domain validation and device admission.
 */
// Validate the buffer contract, then reject nonfinite encoding components before
// writing any record.
ckks_native_wire_result ckks_native_wire_encode_input(
    const ckks_native_input_frame *frame, uint8_t *wire, size_t wire_bytes);
// Decode modulus-major little-endian uint32 values, preserving every residue bit.
ckks_native_wire_result ckks_native_wire_decode_c0(
    const uint8_t *wire, size_t wire_bytes, ckks_native_c0_frame *frame);

#ifdef __cplusplus
}
#endif
#endif
