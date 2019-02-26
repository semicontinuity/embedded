// =============================================================================
// The driver for BUTTON15 (pulled up).
// =============================================================================

#ifndef __DRIVERS__IN__BUTTON15_H
#define __DRIVERS__IN__BUTTON15_H

#include "cpu/avr/gpio.h"
#include <stdint.h>


void button15__init(void) {
    USE_AS_INPUT(IN__BUTTON15);
    ENABLE_PULLUP(IN__BUTTON15);
}

uint8_t button15__get(void) {
    return IS_1(IN__BUTTON15);
}


#endif