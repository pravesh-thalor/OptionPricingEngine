#include "OptionPricingEngine/NormalDistribution.hpp"

#include <cmath>
#include <limits>

namespace ope::normal_distribution {
namespace {

constexpr double kInvSqrt2 = 0.707106781186547524400844362104849039;
constexpr double kInvSqrt2Pi = 0.398942280401432677939946059934381868;

} // namespace

double pdf(double x) noexcept {
    if (std::isnan(x)) {
        return std::numeric_limits<double>::quiet_NaN();
    }

    return kInvSqrt2Pi * std::exp(-0.5 * x * x);
}

double cdf(double x) noexcept {
    if (std::isnan(x)) {
        return std::numeric_limits<double>::quiet_NaN();
    }

    // Phi(x) = 1/2 * erfc(-x/sqrt(2)) provides high numerical accuracy,
    // particularly for tail probabilities.
    return 0.5 * std::erfc(-x * kInvSqrt2);
}

} // namespace ope::normal_distribution
