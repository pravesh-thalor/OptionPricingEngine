#include "OptionPricingEngine/CallPayoff.hpp"

#include <chrono>
#include <cstddef>
#include <iostream>

int main() {
    const ope::CallPayoff call(100.0);
    constexpr std::size_t iterations = 1'000'000;

    const auto start = std::chrono::high_resolution_clock::now();

    double sum = 0.0;
    for (std::size_t i = 0; i < iterations; ++i) {
        sum += call(80.0 + static_cast<double>(i % 60));
    }

    const auto end = std::chrono::high_resolution_clock::now();
    const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Accumulated payoff: " << sum << '\n';
    std::cout << "Elapsed (us): " << duration.count() << '\n';

    return 0;
}
