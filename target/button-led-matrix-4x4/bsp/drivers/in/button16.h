// =============================================================================
// The driver for BUTTON16 (pulled up).
// =============================================================================

#ifndef __DRIVERS__IN__BUTTON16_H
#define __DRIVERS__IN__BUTTON16_H

#include "cpu/avr/gpio.h"
#include <stdint.h>


void button16__init(void) {
    USE_AS_INPUT(IN__BUTTON16);
    ENABLE_PULLUP(IN__BUTTON16);
}

uint8_t button16__get(void) {
    return IS_1(IN__BUTTON16);
}


#endif