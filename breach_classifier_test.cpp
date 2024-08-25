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

TEST(BreachClassifierTestSuite, ClassifyTemperatureBreachTooHigh) {
    // Assume that the upper limit for HI_ACTIVE_COOLING is 45°C
    BatteryCharacter batteryChar = {HI_ACTIVE_COOLING, "BrandY"};
    // Temperature that exceeds the upper limit of 45°C
    BreachType breach = classifyTemperatureBreach(HI_ACTIVE_COOLING, 50.0);
    // Expect breach type to be TOO_HIGH since 50°C > 45°C
    EXPECT_EQ(breach, TOO_HIGH);
}

TEST(CoolingLimitsTestSuite, VerifyCoolingLimits) {
    int lowerLimit = 0, upperLimit = 0;

    getCoolingLimits(HI_ACTIVE_COOLING, &lowerLimit, &upperLimit);
    EXPECT_EQ(lowerLimit, 0);  // Assuming lower limit should be 0
    EXPECT_EQ(upperLimit, 45); // Assuming upper limit should be 45 for HI_ACTIVE_COOLING

    getCoolingLimits(MED_ACTIVE_COOLING, &lowerLimit, &upperLimit);
    EXPECT_EQ(lowerLimit, 0);  // Assuming lower limit should be 0
    EXPECT_EQ(upperLimit, 40); // Assuming upper limit should be 40 for MED_ACTIVE_COOLING

    getCoolingLimits(PASSIVE_COOLING, &lowerLimit, &upperLimit);
    EXPECT_EQ(lowerLimit, 0);  // Assuming lower limit should be 0
    EXPECT_EQ(upperLimit, 35); // Assuming upper limit should be 35 for PASSIVE_COOLING
}
