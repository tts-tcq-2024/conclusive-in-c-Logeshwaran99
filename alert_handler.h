#pragma once
#include "alert_target.h"
#include "battery_character.h"
#include "breach_type.h"

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);
