// =============================================================================
// The driver for BUTTON6 (pulled up).
// =============================================================================

#ifndef __DRIVERS__IN__BUTTON6_H
#define __DRIVERS__IN__BUTTON6_H

#include "cpu/avr/gpio.h"
#include <stdint.h>


void button6__init(void) {
    USE_AS_INPUT(IN__BUTTON6);
    ENABLE_PULLUP(IN__BUTTON6);
}

uint8_t button6__get(void) {
    return IS_1(IN__BUTTON6);
}


#endif