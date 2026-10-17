#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

enum {
    CKKS_INPUT_DEGREE = 8192,
    CKKS_INPUT_MODULI = 6,
    CKKS_INPUT_SEED_BYTES = 64,
};

typedef struct ckks_input_state ckks_input_state;

/* Creation and preparation return NULL on success or a static error message. */
const char *ckks_input_create(
    const char *compact_key_path,
    const uint32_t expected_moduli[CKKS_INPUT_MODULI],
    uint16_t index_map[CKKS_INPUT_DEGREE],
    ckks_input_state **state);

/* Write one input's error samples and per-modulus key/C1 polynomials. */
const char *ckks_input_prepare(
    ckks_input_state *state,
    const uint8_t shareable_seed[CKKS_INPUT_SEED_BYTES],
    const uint8_t error_seed[CKKS_INPUT_SEED_BYTES],
    int8_t error_samples[CKKS_INPUT_DEGREE],
    uint32_t *secret_key[CKKS_INPUT_MODULI],
    uint32_t *c1[CKKS_INPUT_MODULI]);

void ckks_input_destroy(ckks_input_state *state);

#ifdef __cplusplus
}
#endif
