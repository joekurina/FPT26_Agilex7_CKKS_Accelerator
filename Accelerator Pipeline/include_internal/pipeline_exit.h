#pragma once

#include "common.h"
#include "pipes.h"
#include "data_types.h"
#include <cstddef>
#include <sycl/sycl.hpp>
#include <sycl/ext/intel/fpga_extensions.hpp>

namespace ckks {

// Order each sink after its previous chunk, never its current producer.
// The host owns allocation lifetime. Each sink writes the contiguous range
// [P*total_blocks, (P+1)*total_blocks) in NUM_MODULI * total_blocks u32x4 values.

template <int P>
class ExitC0KernelTask;

template <int P>
class ExitC0Kernel {
    u32x4* output_ptr_;
    size_t total_blocks_;

public:
    static_assert(P >= 0 && P < NUM_MODULI, "invalid physical pipeline");
    ExitC0Kernel(u32x4* output, size_t total_blocks)
        : output_ptr_(output), total_blocks_(total_blocks) {}

    void operator()(sycl::handler& h) const {
        u32x4* output_ptr = output_ptr_;
        const size_t total_blocks = total_blocks_;
        h.single_task<ExitC0KernelTask<P>>([=]() [[intel::kernel_args_restrict]] {
            sycl::ext::intel::device_ptr<u32x4> output(output_ptr);
            using Pipes = PipeSet<P>;
            const size_t base = static_cast<size_t>(P) * total_blocks;
            [[intel::initiation_interval(1)]]
            for (size_t blk = 0; blk < total_blocks; ++blk) {
                output[base + blk] = Pipes::PolyAddToExitPipe::read();
            }
        });
    }
};

} // namespace ckks
