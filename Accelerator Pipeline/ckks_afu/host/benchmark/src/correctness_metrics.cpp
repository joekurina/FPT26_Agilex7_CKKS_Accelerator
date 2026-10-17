#include "fpt2026_benchmark/correctness_metrics.hpp"

#include <cmath>
#include <limits>
#include <stdexcept>

namespace fpt2026 {

NumericalMetrics evaluate_slots(
    const std::vector<std::complex<double>>& expected,
    const std::vector<std::complex<double>>& actual,
    std::size_t requested_slot_count,
    double threshold)
{
    if (expected.empty() || expected.size() != actual.size()) {
        throw std::invalid_argument("expected and actual slot vectors must have equal nonzero length");
    }
    if (requested_slot_count > expected.size()) {
        throw std::invalid_argument("requested slot count exceeds vector length");
    }
    if (!std::isfinite(threshold) || threshold < 0.0) {
        throw std::invalid_argument("correctness threshold must be finite and nonnegative");
    }

    NumericalMetrics result;
    result.compared_value_count = expected.size();
    result.threshold = threshold;

    for (std::size_t i = 0; i < expected.size(); ++i) {
        const auto& wanted = expected[i];
        const auto& observed = actual[i];
        const bool finite = std::isfinite(wanted.real()) && std::isfinite(wanted.imag()) &&
                            std::isfinite(observed.real()) && std::isfinite(observed.imag());
        if (!finite) {
            ++result.nonfinite_value_count;
            ++result.mismatch_count;
            result.max_abs_error = std::numeric_limits<double>::infinity();
            continue;
        }
        const double magnitude_error = std::abs(observed - wanted);
        if (magnitude_error > result.max_abs_error) {
            result.max_abs_error = magnitude_error;
        }
        if (magnitude_error > threshold) {
            ++result.mismatch_count;
        }
    }

    result.passed = result.nonfinite_value_count == 0 && result.mismatch_count == 0 &&
                    result.max_abs_error <= threshold;
    return result;
}

} // namespace fpt2026
