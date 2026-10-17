// Per-modulus C0 formation from transformed secret key, message, and supplied C1.
#pragma once

#include <cstddef>

namespace ckks {
    // Compute C0 = message_ntt - key_ntt * C1 mod q_P, lane by lane.
    // C1 is supplied in the matching NTT domain/order.
    template <std::size_t P>
    void polynomial_frame();
} // namespace ckks
