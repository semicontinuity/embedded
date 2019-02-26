// =============================================================================
// The driver for BUTTON8 (pulled up).
// =============================================================================

#ifndef __DRIVERS__IN__BUTTON8_H
#define __DRIVERS__IN__BUTTON8_H

#include "cpu/avr/gpio.h"
#include <stdint.h>


void button8__init(void) {
    USE_AS_INPUT(IN__BUTTON8);
    ENABLE_PULLUP(IN__BUTTON8);
}

uint8_t button8__get(void) {
    return IS_1(IN__BUTTON8);
}


#endif