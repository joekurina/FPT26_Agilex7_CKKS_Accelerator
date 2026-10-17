#pragma once

#include <complex>
#include <cstddef>
#include <vector>

namespace fpt2026 {

struct NumericalMetrics {
    std::size_t compared_value_count{};
    std::size_t nonfinite_value_count{};
    std::size_t mismatch_count{};
    double max_abs_error{};
    double threshold{};
    bool passed{};
};

NumericalMetrics evaluate_slots(
    const std::vector<std::complex<double>>& expected,
    const std::vector<std::complex<double>>& actual,
    std::size_t requested_slot_count,
    double threshold);

} // namespace fpt2026
