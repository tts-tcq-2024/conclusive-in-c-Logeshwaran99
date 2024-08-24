#include "breach_classifier.h"
#include "cooling_limits.h"
#include "infer_breach.h"

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {
    int lowerLimit, upperLimit;
    getCoolingLimits(coolingType, &lowerLimit, &upperLimit);
    return inferBreach(temperatureInC, lowerLimit, upperLimit);
}
