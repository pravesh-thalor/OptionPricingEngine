add_executable(payoff_example
    payoff_example.cpp
)

target_link_libraries(payoff_example
    PRIVATE
        OptionPricingEngine
)

target_set_strict_warnings(payoff_example)
