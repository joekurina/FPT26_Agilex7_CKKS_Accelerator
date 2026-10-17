// SYCL kernel identity and callable for the complete single-frame streaming pipeline.
#pragma once

#include "streaming_pipes.hpp"
#include "ifft.hpp"
#include "ntt.hpp"
#include "poly_add_mult.hpp"

namespace ckks {
    // A type-only name identifies the kernel submitted by the compilation entry point.
    class PipelineKernel;
    // One invocation starts and joins the tasks that consume and produce a frame.
    struct PipelineFrame {
        // Expose the streaming-interface property to the FPGA compiler.
        auto get(properties::properties_tag) {
            return properties::properties{altera::streaming_interface<>};
        }

        // Run the pipeline and emit parser status after every stage has joined.
        void operator()() const;
    };
} // namespace ckks
