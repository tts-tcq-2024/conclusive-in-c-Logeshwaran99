#include <gtest/gtest.h>
#include "email_alert.h"
#include "typewise-alert.h"

TEST(TypeWiseAlertTestSuite, SendToEmail) {
    // Test for TOO_LOW
    testing::internal::CaptureStdout();
    sendToEmail(TOO_LOW);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "To: a.b@c.com\nHi, the temperature is too low\n");

    // Test for TOO_HIGH
    testing::internal::CaptureStdout();
    sendToEmail(TOO_HIGH);
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "To: a.b@c.com\nHi, the temperature is too high\n");

    // Test for NORMAL (should not send an email)
    testing::internal::CaptureStdout();
    sendToEmail(NORMAL);
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "");  // No output expected for NORMAL
}
