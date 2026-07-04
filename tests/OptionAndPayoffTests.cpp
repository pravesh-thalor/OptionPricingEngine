#include "OptionPricingEngine/CallPayoff.hpp"
#include "OptionPricingEngine/EuropeanOption.hpp"
#include "OptionPricingEngine/NormalDistribution.hpp"
#include "OptionPricingEngine/Payoff.hpp"
#include "OptionPricingEngine/PutPayoff.hpp"

#include <gtest/gtest.h>

#include <cmath>
#include <limits>

namespace {

TEST(OptionTests, EuropeanOptionStoresStrikeAndMaturity) {
    constexpr double strike = 100.0;
    constexpr double maturity = 1.5;

    const ope::EuropeanOption option(strike, maturity);

    EXPECT_DOUBLE_EQ(option.strike(), strike);
    EXPECT_DOUBLE_EQ(option.maturity(), maturity);
}

TEST(PayoffTests, CallPayoffReturnsIntrinsicValueAtMaturity) {
    const ope::CallPayoff call(100.0);

    EXPECT_DOUBLE_EQ(call(120.0), 20.0);
    EXPECT_DOUBLE_EQ(call(100.0), 0.0);
    EXPECT_DOUBLE_EQ(call(80.0), 0.0);
}

TEST(PayoffTests, PutPayoffReturnsIntrinsicValueAtMaturity) {
    const ope::PutPayoff put(100.0);

    EXPECT_DOUBLE_EQ(put(80.0), 20.0);
    EXPECT_DOUBLE_EQ(put(100.0), 0.0);
    EXPECT_DOUBLE_EQ(put(120.0), 0.0);
}

TEST(PayoffTests, VirtualInterfaceDispatchesCorrectImplementation) {
    const ope::CallPayoff call(100.0);
    const ope::PutPayoff put(100.0);

    const ope::Payoff& call_as_payoff = call;
    const ope::Payoff& put_as_payoff = put;

    EXPECT_DOUBLE_EQ(call_as_payoff(130.0), 30.0);
    EXPECT_DOUBLE_EQ(put_as_payoff(70.0), 30.0);
}

TEST(NormalDistributionTests, PdfMatchesKnownReferenceValues) {
    constexpr double tolerance = 1e-15;

    EXPECT_NEAR(ope::normal_distribution::pdf(0.0), 0.39894228040143267794, tolerance);
    EXPECT_NEAR(ope::normal_distribution::pdf(1.0), 0.24197072451914334980, tolerance);
    EXPECT_NEAR(ope::normal_distribution::pdf(-1.0), 0.24197072451914334980, tolerance);
}

TEST(NormalDistributionTests, CdfMatchesKnownReferenceValues) {
    constexpr double tolerance = 1e-14;

    EXPECT_NEAR(ope::normal_distribution::cdf(0.0), 0.5, tolerance);
    EXPECT_NEAR(ope::normal_distribution::cdf(1.0), 0.84134474606854294859, tolerance);
    EXPECT_NEAR(ope::normal_distribution::cdf(-1.0), 0.15865525393145705141, tolerance);
    EXPECT_NEAR(ope::normal_distribution::cdf(1.96), 0.9750021048517795230, tolerance);
    EXPECT_NEAR(ope::normal_distribution::cdf(-3.0), 0.0013498980316300933, tolerance);
}

TEST(NormalDistributionTests, CdfSymmetryPropertyHolds) {
    constexpr double x = 1.2345;
    constexpr double tolerance = 1e-14;

    const double left = ope::normal_distribution::cdf(-x);
    const double right = 1.0 - ope::normal_distribution::cdf(x);

    EXPECT_NEAR(left, right, tolerance);
}

TEST(NormalDistributionTests, NanInputPropagatesToNan) {
    const double nan_value = std::numeric_limits<double>::quiet_NaN();

    EXPECT_TRUE(std::isnan(ope::normal_distribution::pdf(nan_value)));
    EXPECT_TRUE(std::isnan(ope::normal_distribution::cdf(nan_value)));
}

} // namespace
