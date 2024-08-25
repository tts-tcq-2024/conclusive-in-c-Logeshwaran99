#include <gtest/gtest.h>
#include "breach_classifier.h"
#include "cooling_limits.h"
#include "infer_breach.h"
#include "typewise-alert.h"

TEST(TypeWiseAlertTestSuite, ClassifyTemperatureBreach) {
    // Test for PASSIVE_COOLING
    EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, 20.0), NORMAL);
    EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, 0.0), NORMAL);
    EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, 36.0), TOO_HIGH);
    EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, -1.0), TOO_LOW);

    // Test for MED_ACTIVE_COOLING
    EXPECT_EQ(classifyTemperatureBreach(MED_ACTIVE_COOLING, 39.0), NORMAL);
    EXPECT_EQ(classifyTemperatureBreach(MED_ACTIVE_COOLING, 40.0), NORMAL);
    EXPECT_EQ(classifyTemperatureBreach(MED_ACTIVE_COOLING, 41.0), TOO_HIGH);
    EXPECT_EQ(classifyTemperatureBreach(MED_ACTIVE_COOLING, -1.0), TOO_LOW);

    // Test for HI_ACTIVE_COOLING
    EXPECT_EQ(classifyTemperatureBreach(HI_ACTIVE_COOLING, 44.0), NORMAL);
    EXPECT_EQ(classifyTemperatureBreach(HI_ACTIVE_COOLING, 45.0), NORMAL);
    EXPECT_EQ(classifyTemperatureBreach(HI_ACTIVE_COOLING, 46.0), TOO_HIGH);
    EXPECT_EQ(classifyTemperatureBreach(HI_ACTIVE_COOLING, 0.0), NORMAL);
    EXPECT_EQ(classifyTemperatureBreach(HI_ACTIVE_COOLING, -5.0), TOO_LOW);
}
TEST(BreachClassifierTestSuite, InvalidCoolingType) {
    // Invalid CoolingType case: Assuming the valid range is from 0 to 2, we'll test with an invalid value like 3
    BreachType breach = classifyTemperatureBreach(static_cast<CoolingType>(3), 25.0);
    EXPECT_EQ(breach, NORMAL);  // Expecting NORMAL as a default since there's no valid mapping
}

TEST(BreachClassifierTestSuite, ExtremelyLowTemperature) {
    // Test with an extremely low temperature, below any reasonable lower limit
    BreachType breach = classifyTemperatureBreach(PASSIVE_COOLING, -1000.0);
    EXPECT_EQ(breach, TOO_LOW);
}

TEST(BreachClassifierTestSuite, ExtremelyHighTemperature) {
    // Test with an extremely high temperature, above any reasonable upper limit
    BreachType breach = classifyTemperatureBreach(HI_ACTIVE_COOLING, 1000.0);
    EXPECT_EQ(breach, TOO_HIGH);
}

TEST(BreachClassifierTestSuite, EdgeCaseLowerLimit) {
    // Test at the exact lower limit for PASSIVE_COOLING
    BreachType breach = classifyTemperatureBreach(PASSIVE_COOLING, 0.0);
    EXPECT_EQ(breach, NORMAL);
}

TEST(BreachClassifierTestSuite, EdgeCaseUpperLimit) {
    // Test at the exact upper limit for HI_ACTIVE_COOLING
    BreachType breach = classifyTemperatureBreach(HI_ACTIVE_COOLING, 45.0);
    EXPECT_EQ(breach, NORMAL);
}

TEST(BreachClassifierTestSuite, SlightlyBelowLowerLimit) {
    // Test slightly below the lower limit for MED_ACTIVE_COOLING
    BreachType breach = classifyTemperatureBreach(MED_ACTIVE_COOLING, -0.1);
    EXPECT_EQ(breach, TOO_LOW);
}

TEST(BreachClassifierTestSuite, SlightlyAboveUpperLimit) {
    // Test slightly above the upper limit for PASSIVE_COOLING
    BreachType breach = classifyTemperatureBreach(PASSIVE_COOLING, 35.1);
    EXPECT_EQ(breach, TOO_HIGH);
}
