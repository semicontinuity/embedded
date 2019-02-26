// =============================================================================
// The driver for BUTTON14 (pulled up).
// =============================================================================

#ifndef __DRIVERS__IN__BUTTON14_H
#define __DRIVERS__IN__BUTTON14_H

#include "cpu/avr/gpio.h"
#include <stdint.h>


void button14__init(void) {
    USE_AS_INPUT(IN__BUTTON14);
    ENABLE_PULLUP(IN__BUTTON14);
}

uint8_t button14__get(void) {
    return IS_1(IN__BUTTON14);
}


#endif