// Compile-time frame geometry, encoding scale, and per-modulus reduction constants.
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace ckks {
    // Degree counts coefficients per modulus.
    // The frame geometry must match the wire layouts and imported transforms.
    inline constexpr std::size_t polynomial_degree = 8192;

    // Coefficient positions grouped in one block.
    inline constexpr std::size_t coefficient_lanes = 4;

    // Each modulus represents the same polynomial in a separate residue plane.
    inline constexpr std::size_t modulus_count = 6;

    // Stage loops count these blocks per frame and require exact divisibility.
    inline constexpr std::size_t blocks_per_frame = polynomial_degree / coefficient_lanes;

    // Encoding scale used when converting real IFFT samples to integer coefficients.
    inline constexpr double scale = 0x1p25;

    // The IFFT output conversion applies this factor, including division by N.
    inline constexpr double coefficient_scale = scale / polynomial_degree;

    // Arithmetic helpers consume each prime together with its split reciprocal.
    struct Modulus {
        std::uint32_t prime;
        // Low and high 32-bit words of floor(2^64 / prime), respectively.
        std::uint32_t barrett_low;
        std::uint32_t barrett_high;
    };

    // P indexes this table and the imported NTT's modulus selector in the same order.
    // All current primes are below 2^31, as required by the modular helper bounds.
    inline constexpr std::array<Modulus, modulus_count> moduli{{
        {1053818881u, 0x135bf4bau, 0x00000004u},
        {1054015489u, 0x132a2218u, 0x00000004u},
        {1054212097u, 0x12f85437u, 0x00000004u},
        {1055260673u, 0x11ef051eu, 0x00000004u},
        {1056178177u, 0x11074e88u, 0x00000004u},
        {1056440321u, 0x10c52d4au, 0x00000004u}
    }};
} // namespace ckks
