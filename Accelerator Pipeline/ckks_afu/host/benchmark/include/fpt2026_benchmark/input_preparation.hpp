#pragma once

#include <array>
#include <complex>
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <string>
#include <vector>

#include "fpt2026_benchmark/benchmark_config.hpp"
#include "fpt2026_benchmark/benchmark_vectors.hpp"

struct ckks_input_state;

namespace fpt2026 {

struct TrialSeeds {
    std::array<std::uint8_t, 64> shareable{};
    std::array<std::uint8_t, 64> error{};
};

TrialSeeds make_trial_seeds(
    const std::string& run_id,
    const std::string& case_id,
    std::size_t repetition,
    std::size_t frame_index);

struct PreparedInput {
    std::vector<std::complex<double>> encoding;
    std::vector<std::int8_t> error;
    std::array<std::vector<std::uint32_t>, kDataModulusCount> secret_key;
    std::array<std::vector<std::uint32_t>, kDataModulusCount> c1;
};

class InputPreparer {
public:
    explicit InputPreparer(const std::filesystem::path& compact_secret_key_path);
    ~InputPreparer();

    InputPreparer(const InputPreparer&) = delete;
    InputPreparer& operator=(const InputPreparer&) = delete;

    PreparedInput prepare(const BenchmarkVector& vector, const TrialSeeds& seeds);

private:
    ckks_input_state* state_{};
    std::vector<std::uint16_t> index_map_;
};

} // namespace fpt2026
