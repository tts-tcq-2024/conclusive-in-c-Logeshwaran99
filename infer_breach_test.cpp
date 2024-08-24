#include <gtest/gtest.h>
#include "infer_breach.h"
#include "breach_type.h"
#include "typewise-alert.h"

TEST(TypeWiseAlertTestSuite, InferBreachEdgeCases) {
    // Test exact limits
    EXPECT_EQ(inferBreach(0.0, 0.0, 35.0), NORMAL); // Lower limit
    EXPECT_EQ(inferBreach(35.0, 0.0, 35.0), NORMAL); // Upper limit

    // Test negative temperature values
    EXPECT_EQ(inferBreach(-10.0, 0.0, 35.0), TOO_LOW); // Below lower limit

    // Test temperature at exactly the upper and lower limit
    EXPECT_EQ(inferBreach(0.0, 0.0, 45.0), NORMAL);
    EXPECT_EQ(inferBreach(45.0, 0.0, 45.0), NORMAL);

    // Test temperature just above the upper limit
    EXPECT_EQ(inferBreach(45.1, 0.0, 45.0), TOO_HIGH);
}

TEST(TypeWiseAlertTestSuite, InferBreachInvalidLimits) {
    // Test where lower limit is greater than upper limit
    EXPECT_EQ(inferBreach(25.0, 30.0, 20.0), TOO_LOW); // Should be considered too low
    EXPECT_EQ(inferBreach(35.0, 30.0, 20.0), TOO_HIGH); // Should be considered too high
}
