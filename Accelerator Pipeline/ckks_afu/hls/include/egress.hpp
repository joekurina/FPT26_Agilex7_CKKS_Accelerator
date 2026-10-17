// Output packetization interface for the per-modulus C0 streams.
#pragma once

namespace ckks {
    // Drain C0 planes in modulus order into DMA beats, with TLAST only at frame end.
    inline void packetize_output_frame();
} // namespace ckks
