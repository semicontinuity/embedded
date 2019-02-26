// =============================================================================
// The driver for BUTTON10 (pulled up).
// =============================================================================

#ifndef __DRIVERS__IN__BUTTON10_H
#define __DRIVERS__IN__BUTTON10_H

#include "cpu/avr/gpio.h"
#include <stdint.h>


void button10__init(void) {
    USE_AS_INPUT(IN__BUTTON10);
    ENABLE_PULLUP(IN__BUTTON10);
}

uint8_t button10__get(void) {
    return IS_1(IN__BUTTON10);
}


#endif