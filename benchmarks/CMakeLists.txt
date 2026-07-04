add_executable(payoff_benchmark
    payoff_benchmark.cpp
)

target_link_libraries(payoff_benchmark
    PRIVATE
        OptionPricingEngine
)

target_set_strict_warnings(payoff_benchmark)
