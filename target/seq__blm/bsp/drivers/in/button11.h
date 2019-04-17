// =============================================================================
// The driver for BUTTON11 (pulled up).
// =============================================================================

#ifndef __DRIVERS__IN__BUTTON11_H
#define __DRIVERS__IN__BUTTON11_H

#include "cpu/avr/gpio.h"
#include <stdint.h>


void button11__init(void) {
    USE_AS_INPUT(IN__BUTTON11);
    ENABLE_PULLUP(IN__BUTTON11);
}

uint8_t button11__get(void) {
    return IS_1(IN__BUTTON11);
}


#endif