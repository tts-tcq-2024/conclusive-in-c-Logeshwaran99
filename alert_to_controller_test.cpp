#include <gtest/gtest.h>
#include "alert_to_controller.h"
#include "typewise-alert.h"

TEST(TypeWiseAlertTestSuite, SendToController) {
    // Test for TOO_LOW
    testing::internal::CaptureStdout();
    sendToController(TOO_LOW);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "feed : 1\n");

    // Test for NORMAL
    testing::internal::CaptureStdout();
    sendToController(NORMAL);
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "feed : 0\n");

    // Test for TOO_HIGH
    testing::internal::CaptureStdout();
    sendToController(TOO_HIGH);
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "feed : 2\n");
}
