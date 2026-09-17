#pragma once

#include "data_types.h"
#include "common.h"
#include "pipe_utils.hpp"
#include <sycl/sycl.hpp>
#include <sycl/ext/intel/fpga_extensions.hpp>

namespace ckks {

// Each edge can buffer a full 2048-block frame. This decouples the
// frame-oriented transforms from their independently blocking consumers.

struct SharedToIFFTPipeId {};
using SharedToIFFTPipe = sycl::ext::intel::pipe<SharedToIFFTPipeId, encoding_block, PIPE_DEPTH_STREAMING>;

struct IFFTToScaleReducePipeArrayId {};
using IFFTToScaleReducePipes = fpga_tools::PipeArray<
    IFFTToScaleReducePipeArrayId,
    encoding_block,
    PIPE_DEPTH_STREAMING,
    NUM_MODULI
>;

// Full-frame buffering isolates the non-stallable RTL from fanout backpressure.
struct IFFTRawOutputPipeId {};
using IFFTRawOutputPipe = sycl::ext::intel::pipe<IFFTRawOutputPipeId, encoding_block, PIPE_DEPTH_BUFFERED>;

// Error fanout (Entry -> ScaleAndReduce x6) BUFFERED: blocked on IFFT
struct ErrorToScaleReducePipeArrayId {};
using ErrorToScaleReducePipes = fpga_tools::PipeArray<
    ErrorToScaleReducePipeArrayId,
    i8x4,
    PIPE_DEPTH_BUFFERED,
    NUM_MODULI
>;

template <int P>
struct PipeSet
{
    struct EntryToNTTAPipeID {};
    struct EntryToPolyMultNegPipeID {};
    struct ScaleReduceToNTTBPipeID {};
    struct NTTAToPolyMultNegPipeID {};
    struct NTTBToPolyAddPipeID {};
    struct PolyAddToExitPipeID {};

    using EntryToNTTAPipe = sycl::ext::intel::pipe<EntryToNTTAPipeID, u32x4, PIPE_DEPTH_STREAMING>;
    // BUFFERED: Entry writes all c1 before PolyMultNegAdd can consume
    using EntryToPolyMultNegPipe = sycl::ext::intel::pipe<EntryToPolyMultNegPipeID, u32x4, PIPE_DEPTH_BUFFERED>;

    using ScaleReduceToNTTBPipe = sycl::ext::intel::pipe<ScaleReduceToNTTBPipeID, u32x4, PIPE_DEPTH_STREAMING>;

    // NTTA may finish while NTTB still waits for IFFT.
    using NTTAToPolyMultNegPipe = sycl::ext::intel::pipe<NTTAToPolyMultNegPipeID, u32x4, PIPE_DEPTH_BUFFERED>;

    using NTTBToPolyAddPipe = sycl::ext::intel::pipe<NTTBToPolyAddPipeID, u32x4, PIPE_DEPTH_STREAMING>;

    using PolyAddToExitPipe = sycl::ext::intel::pipe<PolyAddToExitPipeID, u32x4, PIPE_DEPTH_STREAMING>;
};

}
