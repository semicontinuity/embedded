// =============================================================================
// The driver for BUTTON7 (pulled up).
// =============================================================================

#ifndef __DRIVERS__IN__BUTTON7_H
#define __DRIVERS__IN__BUTTON7_H

#include "cpu/avr/gpio.h"
#include <stdint.h>


void button7__init(void) {
    USE_AS_INPUT(IN__BUTTON7);
    ENABLE_PULLUP(IN__BUTTON7);
}

uint8_t button7__get(void) {
    return IS_1(IN__BUTTON7);
}


#endif