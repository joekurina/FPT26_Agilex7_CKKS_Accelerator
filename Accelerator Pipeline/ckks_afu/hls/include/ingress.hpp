// Fixed-frame DMA parsing and input distribution for the CKKS pipeline.
#pragma once

#include <cstdint>

namespace ckks {
    // Reassemble InputRecords by word count. Bit 0 flags nonzero reserved data.
    inline std::uint32_t parse_input_frame();
    // Route encoding/error to the shared IFFT path, and key/C1 to each modulus.
    inline void distribute_input_frame();
} // namespace ckks
