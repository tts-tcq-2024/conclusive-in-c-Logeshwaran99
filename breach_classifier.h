#pragma once
#include "cooling_type.h"
#include "breach_type.h"

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);
