#include "OptionPricingEngine/PutPayoff.hpp"

#include <algorithm>

namespace ope {

PutPayoff::PutPayoff(double strike)
    : strike_(strike) {}

double PutPayoff::operator()(double spot) const {
    return std::max(strike_ - spot, 0.0);
}

} // namespace ope
