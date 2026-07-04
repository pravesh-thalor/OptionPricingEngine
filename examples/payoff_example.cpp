
#include "OptionPricingEngine/CallPayoff.hpp"
#include "OptionPricingEngine/PutPayoff.hpp"

#include <iostream>

int main() {
    const ope::CallPayoff call(100.0);
    const ope::PutPayoff put(100.0);

    const double spot = 110.0;

    std::cout << "Spot: " << spot << '\n';
    std::cout << "Call payoff: " << call(spot) << '\n';
    std::cout << "Put payoff: " << put(spot) << '\n';

    return 0;
}
