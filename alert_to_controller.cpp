#include "alert_to_controller.h"
#include <stdio.h>

void sendToController(BreachType breachType) {
    const unsigned short header = 0xfeed;
    printf("%x : %x\n", header, breachType);
}
