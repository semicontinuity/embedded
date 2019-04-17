// =============================================================================
// The driver for BUTTON5 (pulled up).
// =============================================================================

#ifndef __DRIVERS__IN__BUTTON5_H
#define __DRIVERS__IN__BUTTON5_H

#include "cpu/avr/gpio.h"
#include <stdint.h>


void button5__init(void) {
    USE_AS_INPUT(IN__BUTTON5);
    ENABLE_PULLUP(IN__BUTTON5);
}

uint8_t button5__get(void) {
    return IS_1(IN__BUTTON5);
}


#endif