// =============================================================================
// The driver for BUTTON3 (pulled up).
// =============================================================================

#ifndef __DRIVERS__IN__BUTTON3_H
#define __DRIVERS__IN__BUTTON3_H

#include "cpu/avr/gpio.h"
#include <stdint.h>


void button3__init(void) {
    USE_AS_INPUT(IN__BUTTON3);
    ENABLE_PULLUP(IN__BUTTON3);
}

uint8_t button3__get(void) {
    return IS_1(IN__BUTTON3);
}


#endif