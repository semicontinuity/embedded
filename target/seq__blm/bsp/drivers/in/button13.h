// =============================================================================
// The driver for BUTTON13 (pulled up).
// =============================================================================

#ifndef __DRIVERS__IN__BUTTON13_H
#define __DRIVERS__IN__BUTTON13_H

#include "cpu/avr/gpio.h"
#include <stdint.h>


void button13__init(void) {
    USE_AS_INPUT(IN__BUTTON13);
    ENABLE_PULLUP(IN__BUTTON13);
}

uint8_t button13__get(void) {
    return IS_1(IN__BUTTON13);
}


#endif