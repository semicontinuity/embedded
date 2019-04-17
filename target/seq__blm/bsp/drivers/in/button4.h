// =============================================================================
// The driver for BUTTON4 (pulled up).
// =============================================================================

#ifndef __DRIVERS__IN__BUTTON4_H
#define __DRIVERS__IN__BUTTON4_H

#include "cpu/avr/gpio.h"
#include <stdint.h>


void button4__init(void) {
    USE_AS_INPUT(IN__BUTTON4);
    ENABLE_PULLUP(IN__BUTTON4);
}

uint8_t button4__get(void) {
    return IS_1(IN__BUTTON4);
}


#endif