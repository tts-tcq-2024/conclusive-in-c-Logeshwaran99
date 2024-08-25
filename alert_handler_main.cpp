#include "alert_handler.h"
#include "breach_classifier.h"
#include "alert_to_controller.h"
#include "email_alert.h"

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {
    BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);
    switch (alertTarget) {
        case TO_CONTROLLER:
            sendToController(breachType);
            break;
        case TO_EMAIL:
            sendToEmail(breachType);
            break;
        default:
            printf("Error: Invalid alert target\n");
            break;
    }
}
