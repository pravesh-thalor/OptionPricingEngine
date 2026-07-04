#include "OptionPricingEngine/CallPayoff.hpp"

#include <algorithm>

namespace ope {

CallPayoff::CallPayoff(double strike)
    : strike_(strike) {}

double CallPayoff::operator()(double spot) const {
    return std::max(spot - strike_, 0.0);
}

} // namespace ope
