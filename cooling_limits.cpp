#include "cooling_limits.h"

void getCoolingLimits(CoolingType coolingType, int* lowerLimit, int* upperLimit) {
    int limits[3][2] = {
        {LOWER_LIMIT_PASSIVE_COOLING, UPPER_LIMIT_PASSIVE_COOLING},
        {LOWER_LIMIT_MED_ACTIVE_COOLING, UPPER_LIMIT_MED_ACTIVE_COOLING},
        {LOWER_LIMIT_HI_ACTIVE_COOLING, UPPER_LIMIT_HI_ACTIVE_COOLING}
    };

    int index = (coolingType == PASSIVE_COOLING) ? 0 :
                (coolingType == MED_ACTIVE_COOLING) ? 1 : 2;

    *lowerLimit = limits[index][0];
    *upperLimit = limits[index][1];
}
