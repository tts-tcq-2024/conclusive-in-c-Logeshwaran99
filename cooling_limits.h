#pragma once
#include "typewise-alert.h"

#define LOWER_LIMIT_PASSIVE_COOLING 0
#define UPPER_LIMIT_PASSIVE_COOLING 35
#define LOWER_LIMIT_MED_ACTIVE_COOLING 0
#define UPPER_LIMIT_MED_ACTIVE_COOLING 40
#define LOWER_LIMIT_HI_ACTIVE_COOLING 0
#define UPPER_LIMIT_HI_ACTIVE_COOLING 45

void getCoolingLimits(CoolingType coolingType, int* lowerLimit, int* upperLimit);
