#include <gtest/gtest.h>
#include "alert_handler.h"
#include "breach_classifier.h"
#include "alert_to_controller.h"
#include "email_alert.h"
#include "typewise-alert.h"

TEST(TypeWiseAlertTestSuite, CheckAndAlertWithVariousTargets) {
    BatteryCharacter batteryChar = {PASSIVE_COOLING, "BrandX"};

    // Test for TO_CONTROLLER
    testing::internal::CaptureStdout();
    checkAndAlert(TO_CONTROLLER, batteryChar, 36.0);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "feed : 2\n");

    // Test for TO_EMAIL
    testing::internal::CaptureStdout();
    checkAndAlert(TO_EMAIL, batteryChar, -1.0);
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "To: a.b@c.com\nHi, the temperature is too low\n");

    // Test normal case (no alert should be sent)
    testing::internal::CaptureStdout();
    checkAndAlert(TO_EMAIL, batteryChar, 25.0);
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "");
}
TEST(TypeWiseAlertTestSuite, CheckAndAlertWithInvalidAlertTarget) {
    BatteryCharacter batteryChar = {PASSIVE_COOLING, "BrandX"};

    // Test with an invalid AlertTarget (e.g., 0, which is not TO_CONTROLLER or TO_EMAIL)
    testing::internal::CaptureStdout();
    checkAndAlert((AlertTarget)0, batteryChar, 25.0); // Cast 0 to AlertTarget enum
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Error: Invalid alert target\n");
}
