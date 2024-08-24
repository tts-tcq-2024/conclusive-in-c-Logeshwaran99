#include <gtest/gtest.h>
#include "cooling_limits.h"
#include "cooling_type.h"
#include "typewise-alert.h"

TEST(TypeWiseAlertTestSuite, GetCoolingLimitsForDifferentCoolingTypes) {
    int lowerLimit, upperLimit;

    // Test for PASSIVE_COOLING
    getCoolingLimits(PASSIVE_COOLING, &lowerLimit, &upperLimit);
    EXPECT_EQ(lowerLimit, 0);
    EXPECT_EQ(upperLimit, 35);

    // Test for MED_ACTIVE_COOLING
    getCoolingLimits(MED_ACTIVE_COOLING, &lowerLimit, &upperLimit);
    EXPECT_EQ(lowerLimit, 0);
    EXPECT_EQ(upperLimit, 40);

    // Test for HI_ACTIVE_COOLING
    getCoolingLimits(HI_ACTIVE_COOLING, &lowerLimit, &upperLimit);
    EXPECT_EQ(lowerLimit, 0);
    EXPECT_EQ(upperLimit, 45);

    // Test for invalid CoolingType (simulate with casting an out-of-range value)
    getCoolingLimits((CoolingType)999, &lowerLimit, &upperLimit);
    EXPECT_EQ(lowerLimit, 0);
    EXPECT_EQ(upperLimit, 45); // Should default to the highest cooling limit
}
