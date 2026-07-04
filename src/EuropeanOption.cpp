#include "OptionPricingEngine/EuropeanOption.hpp"

namespace ope {

EuropeanOption::EuropeanOption(double strike, double maturity)
    : Option(strike, maturity) {}

} // namespace ope
