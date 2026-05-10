#ifndef __OUT_VALVE_H
#define __OUT_VALVE_H

#include "cpu/avr/gpio.h"
#include <stdbool.h>


static inline void valve__init(void) {
    USE_AS_OUTPUT(VALVE);
}


static inline void valve__on(void) {
    OUT_1(VALVE);
}


static inline void valve__off(void) {
    OUT_0(VALVE);
}


#endif