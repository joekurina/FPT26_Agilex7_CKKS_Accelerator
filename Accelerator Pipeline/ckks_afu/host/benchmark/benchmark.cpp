// Prepare inputs, time complete-ciphertext delivery, and verify retained results.

#include "benchmark.hpp"
#include "ckks_native.h"
#include "fpt2026_benchmark/input_preparation.hpp"
#include "fpt2026_benchmark/seal_oracle.hpp"
#include "fpt2026_benchmark/correctness_metrics.hpp"
#include "seal/seal.h"

#include <algorithm>
#include <array>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

namespace ckks {
namespace {
using Clock = std::chrono::steady_clock;
using Limbs = std::array<std::vector<std::uint32_t>, fpt2026::kDataModulusCount>;

// Keep expected slots and the exact submitted C1 alongside each reusable wire frame.
// The accelerator returns only C0, so C1 is needed for later SEAL reconstruction.
struct PreparedFrame {
    fpt2026::BenchmarkVector vector;
    std::vector<std::uint8_t> wire;
    Limbs c1;
};

// Abort a failed benchmark contract through the caller's exception path.
void require(bool condition, const char* message) {
    if (!condition) throw std::runtime_error(message);
}

// Allocate the two-polynomial, first-data-level SEAL container during setup.
// The backend already produces NTT-domain residues at the fixed benchmark scale.
seal::Ciphertext allocate_ciphertext(const fpt2026::SealOracle& oracle) {
    seal::Ciphertext ciphertext;
    ciphertext.resize(oracle.context(), oracle.context().first_parms_id(), 2);
    ciphertext.is_ntt_form() = true;
    ciphertext.scale() = fpt2026::kScale;
    std::fill_n(ciphertext.data(), 2 * fpt2026::kPolyModulusDegree *
                fpt2026::kDataModulusCount, std::uint64_t{0});
    return ciphertext;
}

// Widen residues into the SEAL polynomial-major ciphertext layout.
// Allocate before timing and validate retained samples after each trial.
void materialize(seal::Ciphertext& ciphertext, const ckks_native_c0_frame& c0, const Limbs& c1) {
    // SEAL stores each polynomial as uint64 values. Widen residues
    // individually, joining returned C0 with retained C1.
    for (std::size_t p = 0; p < fpt2026::kDataModulusCount; ++p) {
        const auto offset = p * fpt2026::kPolyModulusDegree;
        auto* out0 = ciphertext.data(0) + offset;
        auto* out1 = ciphertext.data(1) + offset;
        for (std::size_t i = 0; i < fpt2026::kPolyModulusDegree; ++i) {
            out0[i] = static_cast<std::uint64_t>(c0.coefficients[p][i]);
            out1[i] = static_cast<std::uint64_t>(c1[p][i]);
        }
    }
}

// Check then decrypt/decode with the matching key.
void verify(const char* phase, std::size_t index, const PreparedFrame& frame,
            const seal::Ciphertext& ciphertext, const fpt2026::SealOracle& oracle) {
    std::size_t noncanonical = 0, c1_mismatch = 0;
    for (std::size_t p = 0; p < fpt2026::kDataModulusCount; ++p) {
        for (std::size_t i = 0; i < fpt2026::kPolyModulusDegree; ++i) {
            const auto offset = p * fpt2026::kPolyModulusDegree + i;
            noncanonical += ciphertext.data(0)[offset] >= fpt2026::kDataModuli[p];
            noncanonical += ciphertext.data(1)[offset] >= fpt2026::kDataModuli[p];
            c1_mismatch += ciphertext.data(1)[offset] != frame.c1[p][i];
        }
    }
    std::cout << "TRANSPORT phase=" << phase << " index=" << index
              << " noncanonical=" << noncanonical << " c1_mismatch=" << c1_mismatch << '\n';
    require(noncanonical == 0 && c1_mismatch == 0, "Ciphertext residue contract failed");

    // evaluate_slots compares the full slot vector
    const auto decoded = oracle.decrypt_decode(ciphertext);
    const auto metrics = fpt2026::evaluate_slots(frame.vector.slots, decoded,
        frame.vector.active_slots, fpt2026::kCorrectnessThreshold);
    std::cout << std::setprecision(17) << "FULL_SEAL phase=" << phase
              << " index=" << index << " case=" << frame.vector.id
              << " compared=" << metrics.compared_value_count
              << " mismatches=" << metrics.mismatch_count
              << " nonfinite=" << metrics.nonfinite_value_count
              << " max_abs_error=" << metrics.max_abs_error
              << " threshold=" << metrics.threshold << " passed=" << metrics.passed << std::endl;
    require(metrics.compared_value_count == fpt2026::kSlotCount && metrics.passed,
            "SEAL full-slot verification failed");
}
}

// Prepare inputs and warm up before timing. Verify retained samples afterward.
int run_native_benchmark(const NativeBenchmarkOptions& options,
                         NativeFrameFunction execute, void* device) {
    static_assert(CKKS_NATIVE_POLY_N == fpt2026::kPolyModulusDegree);
    static_assert(CKKS_NATIVE_NUM_MODULI == fpt2026::kDataModulusCount);

    // Timer covers host keys, input preparation and ciphertext allocation.
    const auto setup_start = Clock::now();
    fpt2026::SealOracle oracle(options.seal_key);
    fpt2026::InputPreparer preparation(options.compact_key);
    const auto cases = fpt2026::all_vector_cases();
    std::vector<PreparedFrame> corpus;
    corpus.reserve(2 * cases.size());
    auto input = std::make_unique<ckks_native_input_frame>();

    // Prepare the base cases and a scaled second set.
    // Reuse these inputs and C1 values throughout the run.
    for (std::size_t frame = 0; frame < 2 * cases.size(); ++frame) {
        auto vector = fpt2026::generate_benchmark_vector(cases[frame % cases.size()]);
        if (frame >= cases.size()) {
            for (auto& value : vector.slots) {
                value *= 1.125;
            }
        }
        const auto seed = fpt2026::make_trial_seeds("native-CKKS-AHLS-prepared-v1", vector.id, frame, 0);

        auto prepared = preparation.prepare(vector, seed);
        // Preserve the prepared SEAL-Embedded embedding's index order and conjugate
        // each complex value for the DSP-facing IFFT input.
        for (std::size_t i = 0; i < CKKS_NATIVE_POLY_N; ++i) {
            input->encoding[i] = {prepared.encoding[i].real(), -prepared.encoding[i].imag()};
            input->error[i] = prepared.error[i];
        }
        // Keys remain in coefficient order for the device's key NTT. C1 is consumed
        // alongside NTT output in its prepared modulus/index order.
        for (std::size_t p = 0; p < CKKS_NATIVE_NUM_MODULI; ++p) {
            std::copy(prepared.secret_key[p].begin(), prepared.secret_key[p].end(), input->secret_key[p]);
            std::copy(prepared.c1[p].begin(), prepared.c1[p].end(), input->c1[p]);
        }
        // Retain the payload's C1 residues for reconstruction with returned C0.
        PreparedFrame item{std::move(vector), std::vector<std::uint8_t>(CKKS_NATIVE_INPUT_BYTES),
                           std::move(prepared.c1)};
        require(ckks_native_wire_encode_input(input.get(), item.wire.data(), item.wire.size()) ==
                CKKS_NATIVE_WIRE_OK, "Input serialization failed");
        corpus.push_back(std::move(item));
    }
    input.reset();
    auto c0 = std::make_unique<ckks_native_c0_frame>();
    auto working = allocate_ciphertext(oracle);

    // Preallocate sample destinations so timed retention uses swaps.
    std::vector<std::size_t> sample_indices{0, options.frames / 2, options.frames - 1};
    std::vector<seal::Ciphertext> samples;
    samples.reserve(sample_indices.size());
    for (std::size_t i = 0; i < sample_indices.size(); ++i) samples.push_back(allocate_ciphertext(oracle));
    const auto setup_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(Clock::now() - setup_start).count();
    std::cout << "BENCHMARK boundary=native_prepared_full_ciphertext_v1 device_admission=1"
              << " input_bytes=" << CKKS_NATIVE_INPUT_BYTES << " output_bytes=" << CKKS_NATIVE_C0_BYTES
              << " reused_prepared_corpus=" << corpus.size() << " host_setup_ns=" << setup_ns
              << " frames_per_trial=" << options.frames << " trials=" << options.repetitions
              << " warmup=" << options.warmup << " samples_per_trial=" << samples.size() << std::endl;

    // Consume backend-owned C0 before the next submission can overwrite it.
    // Delivery includes wire decoding and full ciphertext materialization.
    auto deliver = [&](const PreparedFrame& frame, seal::Ciphertext& destination) {
        const auto* output = execute(device, frame.wire.data(), frame.wire.size());
        require(output, "Native backend returned no C0 buffer");
        require(ckks_native_wire_decode_c0(output, CKKS_NATIVE_C0_BYTES, c0.get()) == CKKS_NATIVE_WIRE_OK,
                "Output deserialization failed");
        materialize(destination, *c0, frame.c1);
    };

    // Warmup
    for (std::size_t i = 0; i < options.warmup; ++i) {
        deliver(corpus[i % corpus.size()], working);
    }

    std::cout << "WARMUP completed=" << options.warmup << " numerically_checked=0" << std::endl;

    std::uint64_t total_ns = 0, total_frames = 0;
    for (std::size_t trial = 0; trial < options.repetitions; ++trial) {
        std::size_t sample = 0;
        // Wall time includes input copying, native submit/wait/release, C0 decoding,
        // C0/C1 assembly, sample swaps and deadline checks.
        const auto start = Clock::now();
        const auto deadline = start + std::chrono::seconds(options.trial_deadline_seconds);
        for (std::size_t i = 0; i < options.frames; ++i) {
            deliver(corpus[i % corpus.size()], working);
            if (sample < sample_indices.size() && i == sample_indices[sample]) {
                std::swap(working, samples[sample]);
                ++sample;
            }
            // Enforce the trial bound only after the backend has returned a completed frame.
            require(Clock::now() <= deadline, "Benchmark trial deadline exceeded after completed frame");
        }
        // Stop timing before numerical validation of retained samples.
        const auto end = Clock::now();
        const auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        std::cout << "TRIAL_TIMING trial=" << trial << " frames=" << options.frames
                  << " elapsed_ns=" << elapsed_ns << " validation=pending" << std::endl;
        require(elapsed_ns > 0 && sample == samples.size(), "Invalid timing or retained-sample count");
        for (std::size_t j = 0; j < sample_indices.size(); ++j)
            verify("measured_sample", sample_indices[j], corpus[sample_indices[j] % corpus.size()], samples[j], oracle);
        // Accept timing into the aggregate only after every retained sample passes.
        total_ns += static_cast<std::uint64_t>(elapsed_ns);
        total_frames += options.frames;
        std::cout << std::setprecision(17) << "THROUGHPUT trial=" << trial
                  << " frames=" << options.frames << " elapsed_ns=" << elapsed_ns
                  << " ciphertexts_per_second=" << static_cast<double>(options.frames) * 1e9 / elapsed_ns
                  << " verified_samples=" << samples.size() << " passed=1" << std::endl;
    }
    // Aggregate throughput
    std::cout << "FPGA_TEST_PASSED qualification_frames=0"
              << " measured_frames=" << total_frames << " total_measured_ns=" << total_ns
              << " verified_measured_samples=" << options.repetitions * samples.size()
              << " weighted_ciphertexts_per_second=" << static_cast<double>(total_frames) * 1e9 / total_ns
              << " unsampled_outputs_numerically_verified=0" << std::endl;
    return 0;
}
}
