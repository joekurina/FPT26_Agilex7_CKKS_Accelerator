// Benchmark orchestration around one synchronous native frame call.

#pragma once

#include <cstddef>
#include <cstdint>
#include <filesystem>

namespace ckks {
// Measured frame counts apply per trial. Warmup runs once before all trials,
// and each submission reuses the prepared input corpus.
struct NativeBenchmarkOptions {
    // Matching compact and serialized forms of the benchmark secret key.
    std::filesystem::path compact_key;
    std::filesystem::path seal_key;
    std::size_t frames = 1024;
    std::size_t warmup = 32;
    std::size_t repetitions = 3;
    // Checked after completed frames.
    unsigned trial_deadline_seconds = 120;
};

// The backend copies the prepared input, submits one frame, waits for fenced
// completion, verifies its sequence/error status, and releases admission.
// Returned C0 storage remains owned and pinned until the next invocation.
// An uncertain DMA owner must remain alive with its allocations and handles retained.
// Frame-admission release retains the backend's DMA allocation.
using NativeFrameFunction = const std::uint8_t* (*)(
    void* device, const std::uint8_t* input, std::size_t input_bytes);

// Prepare inputs and warm up, then time delivery plus full C0/C1 assembly.
// Check the retained first, middle and last result after each trial.
int run_native_benchmark(const NativeBenchmarkOptions& options,
                         NativeFrameFunction execute, void* device);
}
