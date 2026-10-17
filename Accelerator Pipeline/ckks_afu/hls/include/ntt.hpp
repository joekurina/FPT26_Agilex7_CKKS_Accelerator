// Role-specific stream adapters around the supplied NTT library.
#pragma once

#include <cstddef>

namespace ckks {
    // Key input is already in residue form. Message input is a shared signed value
    // that this adapter reduces modulo q_P before calling the transform.
    enum class NttRole { key, message };

    // P selects the modulus. Role selects key or message FIFOs.
    // Process one frame, including message-input reduction, and emit transformed blocks.
    template <std::size_t P, NttRole Role>
    void ntt_frame();
} // namespace ckks
