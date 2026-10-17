#include "fpt2026_benchmark/input_preparation.hpp"

#include <algorithm>
#include <stdexcept>

#include "fpt2026_benchmark/seal_oracle.hpp"
#include "seal_embedded_bridge.h"

namespace fpt2026 {
namespace {

struct TrialDescriptor {
    std::string run_id;
    std::string case_id;
    std::size_t repetition{};
    std::size_t frame_index{};
    std::string purpose;
    std::int32_t prime_index{-1};
};

std::string trial_seed_domain(const TrialDescriptor& descriptor)
{
    if (descriptor.run_id.empty() || descriptor.case_id.empty() ||
        descriptor.purpose.empty()) {
        throw std::invalid_argument("trial seed descriptor contains an empty identity field");
    }
    return "FPT2026/randomness/v1/" + descriptor.run_id + '/' +
           descriptor.case_id + '/' + std::to_string(descriptor.repetition) + '/' +
           std::to_string(descriptor.frame_index) + '/' + descriptor.purpose + '/' +
           std::to_string(descriptor.prime_index);
}

std::array<std::uint8_t, 64> derive_trial_seed(const TrialDescriptor& descriptor)
{
    const auto bytes = shake256(trial_seed_domain(descriptor), 64);
    std::array<std::uint8_t, 64> result{};
    std::copy(bytes.begin(), bytes.end(), result.begin());
    return result;
}

} // namespace

static_assert(kPolyModulusDegree == CKKS_INPUT_DEGREE &&
              kDataModulusCount == CKKS_INPUT_MODULI &&
              TrialSeeds{}.shareable.size() == CKKS_INPUT_SEED_BYTES &&
              TrialSeeds{}.error.size() == CKKS_INPUT_SEED_BYTES);

TrialSeeds make_trial_seeds(
    const std::string& run_id,
    const std::string& case_id,
    std::size_t repetition,
    std::size_t frame_index)
{
    TrialSeeds result;
    result.shareable = derive_trial_seed(
        TrialDescriptor{run_id, case_id, repetition, frame_index, "uniform-c1", -1});
    result.error = derive_trial_seed(
        TrialDescriptor{run_id, case_id, repetition, frame_index, "ckks-error", -1});
    return result;
}

InputPreparer::InputPreparer(const std::filesystem::path& compact_secret_key_path)
    : index_map_(kPolyModulusDegree)
{
    const auto key_path = require_key_file(compact_secret_key_path);
    const std::string key_string = key_path.string();
    if (const char* error = ckks_input_create(
            key_string.c_str(), kDataModuli.data(), index_map_.data(), &state_)) {
        throw std::runtime_error(error);
    }
}

InputPreparer::~InputPreparer()
{
    ckks_input_destroy(state_);
}

PreparedInput InputPreparer::prepare(const BenchmarkVector& vector, const TrialSeeds& seeds)
{
    PreparedInput result;
    result.encoding = make_conjugate_embedding(vector, index_map_);
    result.error.resize(kPolyModulusDegree);
    std::array<std::uint32_t*, kDataModulusCount> secret_key{};
    std::array<std::uint32_t*, kDataModulusCount> c1{};
    for (std::size_t p = 0; p < kDataModulusCount; ++p) {
        result.secret_key[p].resize(kPolyModulusDegree);
        result.c1[p].resize(kPolyModulusDegree);
        secret_key[p] = result.secret_key[p].data();
        c1[p] = result.c1[p].data();
    }
    if (const char* error = ckks_input_prepare(
            state_, seeds.shareable.data(), seeds.error.data(), result.error.data(),
            secret_key.data(), c1.data())) {
        throw std::runtime_error(error);
    }
    return result;
}

} // namespace fpt2026
