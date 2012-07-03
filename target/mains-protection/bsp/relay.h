#ifndef __RELAY_H
#define __RELAY_H

#include "device.h"
#include "cpu/avr/gpio.h"

inline void relay__init(void) {
    USE_AS_OUTPUT(RELAY);
}

inline void relay__on(void) {
    OUT_1(RELAY);
}

inline void relay__off(void) {
    OUT_0(RELAY);
}

#endif