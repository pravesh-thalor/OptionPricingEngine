cmake_minimum_required(VERSION 3.20)

project(OptionPricingEngine VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(OPTION_PRICING_ENGINE_BUILD_TESTS "Build unit tests" ON)
option(OPTION_PRICING_ENGINE_BUILD_EXAMPLES "Build examples" ON)
option(OPTION_PRICING_ENGINE_BUILD_BENCHMARKS "Build benchmarks" ON)

include(cmake/CompilerWarnings.cmake)

add_library(OptionPricingEngine
    src/Option.cpp
    src/EuropeanOption.cpp
    src/CallPayoff.cpp
    src/PutPayoff.cpp
    src/NormalDistribution.cpp
)

add_library(OptionPricingEngine::OptionPricingEngine ALIAS OptionPricingEngine)

target_include_directories(OptionPricingEngine
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

target_set_strict_warnings(OptionPricingEngine)

if(OPTION_PRICING_ENGINE_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(OPTION_PRICING_ENGINE_BUILD_BENCHMARKS)
    add_subdirectory(benchmarks)
endif()

if(OPTION_PRICING_ENGINE_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
