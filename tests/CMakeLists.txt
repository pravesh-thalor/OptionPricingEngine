include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(option_pricing_engine_tests
    OptionAndPayoffTests.cpp
)

target_link_libraries(option_pricing_engine_tests
    PRIVATE
        OptionPricingEngine
        GTest::gtest_main
)

target_set_strict_warnings(option_pricing_engine_tests)

include(GoogleTest)
gtest_discover_tests(option_pricing_engine_tests)
