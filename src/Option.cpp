#include "OptionPricingEngine/Option.hpp"

namespace ope {

Option::Option(double strike, double maturity)
    : strike_(strike), maturity_(maturity) {}

double Option::strike() const noexcept {
    return strike_;
}

double Option::maturity() const noexcept {
    return maturity_;
}

} // namespace ope
