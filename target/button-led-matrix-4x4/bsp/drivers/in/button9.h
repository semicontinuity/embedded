// =============================================================================
// The driver for BUTTON9 (pulled up).
// =============================================================================

#ifndef __DRIVERS__IN__BUTTON9_H
#define __DRIVERS__IN__BUTTON9_H

#include "cpu/avr/gpio.h"
#include <stdint.h>


void button9__init(void) {
    USE_AS_INPUT(IN__BUTTON9);
    ENABLE_PULLUP(IN__BUTTON9);
}

uint8_t button9__get(void) {
    return IS_1(IN__BUTTON9);
}


#endif