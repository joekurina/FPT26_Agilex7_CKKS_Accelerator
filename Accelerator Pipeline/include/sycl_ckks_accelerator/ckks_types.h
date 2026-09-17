#pragma once

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
#include <complex>
typedef std::complex<double> complex_double;
#else
#include <complex.h>
typedef double complex complex_double;
#endif

/* Fixed image configuration, shared by C/C++ callers and device code.
 * One physical pipeline per modulus. These are not independent dimensions. */
#define POLY_N 8192
#define NUM_MODULI 6
#define LANES 4
#define CHUNK_FRAMES 4
#define RING_SLOTS 2
#define SCALE 0x1p25
