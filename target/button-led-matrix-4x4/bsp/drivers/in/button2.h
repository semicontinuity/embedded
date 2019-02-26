// =============================================================================
// The driver for BUTTON2 (pulled up).
// =============================================================================

#ifndef __DRIVERS__IN__BUTTON2_H
#define __DRIVERS__IN__BUTTON2_H

#include "cpu/avr/gpio.h"
#include <stdint.h>


void button2__init(void) {
    USE_AS_INPUT(IN__BUTTON2);
    ENABLE_PULLUP(IN__BUTTON2);
}

uint8_t button2__get(void) {
    return IS_1(IN__BUTTON2);
}


#endif