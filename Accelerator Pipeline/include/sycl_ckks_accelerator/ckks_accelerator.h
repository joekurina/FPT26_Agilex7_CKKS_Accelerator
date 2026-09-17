#pragma once

#include "sycl_ckks_accelerator/ckks_types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ckks_accelerator ckks_accelerator;
typedef uint32_t ckks_status;
enum {
    CKKS_STATUS_SUCCESS = 0u,
    CKKS_STATUS_INVALID_ARGUMENT = 1u,
    CKKS_STATUS_RUNTIME_ERROR = 4u,
    CKKS_STATUS_BUSY = 7u,
    CKKS_STATUS_NOT_READY = 8u,
    CKKS_STATUS_TIMEOUT = 9u
};

/* Fixed runtime: N=8192, six ordered moduli, scale=2^25, four frames
 * per enqueue and two host slots. Externally serialize calls. One accelerator per
 * process. Close does not restart persistent services. The ordered moduli are
 * 1053818881, 1054015489, 1054212097, 1055260673, 1056178177, 1056440321.
 * Arrays contain four frame-major polynomials per modulus. Inputs are copied
 * before enqueue returns. */
int ckks_create(ckks_accelerator **accelerator, char *error_message, size_t error_message_capacity);

/* Appends one chunk in FIFO order. BUSY accepts nothing: both slots still
 * belong to uncollected outputs, even when their work is complete. */
int ckks_enqueue(ckks_accelerator *accelerator, size_t frame_count,
    const complex_double *encoding_buffers, const int8_t *error_samples,
    const uint32_t *const *secret_keys, const uint32_t *const *uniform_polys,
    char *error_message, size_t error_message_capacity);

/* Nonblocking query of the oldest uncollected output only. Never releases it.
 * SUCCESS sets ready to 0 or 1, covering every ingress worker and the download.
 * Empty queue: INVALID_ARGUMENT ("no pending FPGA output"), with ready=0. */
int ckks_poll(ckks_accelerator *accelerator,
    uint32_t *ready,
    char *error_message, size_t error_message_capacity);

/* Nonblocking FIFO collection: copies full C0 and retained C1, then releases
 * the oldest slot exactly once. NOT_READY leaves it pending if unfinished.
 * Empty queue: INVALID_ARGUMENT  ("no pending FPGA output"). */
int ckks_collect_next(ckks_accelerator *accelerator,
    uint32_t **c0_outputs, uint32_t **c1_outputs,
    char *error_message, size_t error_message_capacity);

/* Waits for all outstanding work, without collecting or releasing any output.
 * Empty queue succeeds. */
int ckks_drain(ckks_accelerator *accelerator, uint64_t timeout_ns,
    char *error_message, size_t error_message_capacity);

/* Collect all outputs first (otherwise BUSY). Frees buffers, retains the
 * object/queue, and never waits for persistent services. No restart is allowed. */
int ckks_close(ckks_accelerator *accelerator,
    char *error_message, size_t error_message_capacity);

#ifdef __cplusplus
}
#endif
