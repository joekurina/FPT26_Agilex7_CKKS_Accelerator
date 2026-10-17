#include "seal_embedded_bridge.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ckks_common.h"
#include "ckks_sym.h"
#include "parameters.h"
#include "sample.h"

#ifndef SE_USE_MALLOC
#error "The Native input preparation requires the SE_USE_MALLOC SEAL-Embedded configuration"
#endif

_Static_assert(sizeof(ZZ) == sizeof(uint32_t),
               "FPT 2026 requires the 32-bit SEAL-Embedded residue ABI");
_Static_assert(sizeof(flpt) == sizeof(float),
               "FPT 2026 requires the 32-bit SEAL-Embedded real input ABI");

struct ckks_input_state {
    Parms parms;
    ZZ *mempool;
    SE_PTRS ptrs;
    SE_PRNG shareable_prng;
    SE_PRNG error_prng;
};

static const char *load_compact_key_packed(const char *path, ZZ *loaded_key)
{
    const size_t key_bytes = CKKS_INPUT_DEGREE / 4u;
    FILE *stream = fopen(path, "rb");
    int trailing;

    if (stream == NULL) {
        return "cannot open compact benchmark key";
    }
    memset(loaded_key, 0, key_bytes);
    if (fread((unsigned char *)loaded_key, 1u, key_bytes, stream) != key_bytes) {
        fclose(stream);
        return "compact benchmark key has the wrong size";
    }
    trailing = fgetc(stream);
    fclose(stream);
    if (trailing != EOF) {
        return "compact benchmark key has trailing bytes";
    }
    return NULL;
}

const char *ckks_input_create(
    const char *compact_key_path,
    const uint32_t expected_moduli[CKKS_INPUT_MODULI],
    uint16_t index_map[CKKS_INPUT_DEGREE],
    ckks_input_state **state)
{
    ckks_input_state *created;
    const char *error;
    size_t p;

    *state = NULL;
    created = (ckks_input_state *)calloc(1u, sizeof(*created));
    if (created == NULL) {
        return "cannot allocate SEAL-Embedded state";
    }
    created->parms.is_asymmetric = false;
    created->parms.small_s = true;
    created->parms.sample_s = false;
    created->mempool = ckks_mempool_setup_sym(CKKS_INPUT_DEGREE);
    if (created->mempool == NULL) {
        free(created);
        return "cannot allocate SEAL-Embedded memory pool";
    }
    ckks_set_ptrs_sym(CKKS_INPUT_DEGREE, created->mempool, &created->ptrs);
    ckks_setup(CKKS_INPUT_DEGREE, CKKS_INPUT_MODULI,
               created->ptrs.index_map_ptr, &created->parms);

    for (p = 0; p < CKKS_INPUT_MODULI; ++p) {
        if (created->parms.moduli[p].value != expected_moduli[p]) {
            ckks_input_destroy(created);
            return "SEAL-Embedded modulus contract mismatch";
        }
    }
    created->parms.sample_s = false;
    error = load_compact_key_packed(compact_key_path, created->ptrs.ternary);
    if (error != NULL) {
        ckks_input_destroy(created);
        return error;
    }
    memcpy(index_map, created->ptrs.index_map_ptr,
           CKKS_INPUT_DEGREE * sizeof(*index_map));
    *state = created;
    return NULL;
}

const char *ckks_input_prepare(
    ckks_input_state *state,
    const uint8_t shareable_seed[CKKS_INPUT_SEED_BYTES],
    const uint8_t error_seed[CKKS_INPUT_SEED_BYTES],
    int8_t error_samples[CKKS_INPUT_DEGREE],
    uint32_t *secret_key[CKKS_INPUT_MODULI],
    uint32_t *c1[CKKS_INPUT_MODULI])
{
    uint8_t share_seed_copy[CKKS_INPUT_SEED_BYTES];
    uint8_t error_seed_copy[CKKS_INPUT_SEED_BYTES];
    size_t p;

    memcpy(share_seed_copy, shareable_seed, sizeof(share_seed_copy));
    memcpy(error_seed_copy, error_seed, sizeof(error_seed_copy));
    prng_randomize_reset(&state->shareable_prng, share_seed_copy);
    prng_randomize_reset(&state->error_prng, error_seed_copy);
    sample_poly_cbd_generic_prng_16(
        CKKS_INPUT_DEGREE, &state->error_prng, error_samples);

    ckks_reset_primes(&state->parms);
    for (p = 0; p < CKKS_INPUT_MODULI; ++p) {
        expand_poly_ternary(state->ptrs.ternary, &state->parms, secret_key[p]);
        sample_poly_uniform(&state->parms, &state->shareable_prng, c1[p]);
        if (p + 1u < CKKS_INPUT_MODULI &&
            !ckks_next_prime_sym(&state->parms, NULL)) {
            return "modulus chain ended during accelerator preparation";
        }
    }
    return NULL;
}

void ckks_input_destroy(ckks_input_state *state)
{
    if (state == NULL) {
        return;
    }
    if (state->parms.moduli != NULL) {
        delete_parameters(&state->parms);
    }
    free(state->mempool);
    state->mempool = NULL;
    free(state);
}
