// =============================================================================
// The driver for BUTTON0 (pulled up).
// =============================================================================

#ifndef __DRIVERS__IN__BUTTON0_H
#define __DRIVERS__IN__BUTTON0_H

#include "cpu/avr/gpio.h"
#include <stdint.h>


void button0__init(void) {
    USE_AS_INPUT(IN__BUTTON0);
    ENABLE_PULLUP(IN__BUTTON0);
}

uint8_t button0__get(void) {
    return IS_1(IN__BUTTON0);
}


#endif