// =============================================================================
// The driver for BUTTON1 (pulled up).
// =============================================================================

#ifndef __DRIVERS__IN__BUTTON1_H
#define __DRIVERS__IN__BUTTON1_H

#include "cpu/avr/gpio.h"
#include <stdint.h>


void button1__init(void) {
    USE_AS_INPUT(IN__BUTTON1);
    ENABLE_PULLUP(IN__BUTTON1);
}

uint8_t button1__get(void) {
    return IS_1(IN__BUTTON1);
}


#endif