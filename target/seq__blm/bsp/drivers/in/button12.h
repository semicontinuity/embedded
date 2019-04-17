// =============================================================================
// The driver for BUTTON12 (pulled up).
// =============================================================================

#ifndef __DRIVERS__IN__BUTTON12_H
#define __DRIVERS__IN__BUTTON12_H

#include "cpu/avr/gpio.h"
#include <stdint.h>


void button12__init(void) {
    USE_AS_INPUT(IN__BUTTON12);
    ENABLE_PULLUP(IN__BUTTON12);
}

uint8_t button12__get(void) {
    return IS_1(IN__BUTTON12);
}


#endif