// Handwritten adapters between pipeline blocks and the imported four-lane IFFT.
#pragma once

namespace ckks {
    // Pair EncodingInput and IfftError blocks with their corresponding IFFT returns.
    // Scale, round, convert to int64 and add error before writing IfftOutput.
    inline void ifft_frame();
    // Copy each shared signed block directly to every message-role NTT input.
    inline void fanout_ifft_frame_blocking();
} // namespace ckks
