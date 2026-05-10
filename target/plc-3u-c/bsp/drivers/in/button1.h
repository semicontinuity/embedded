// =============================================================================
// The driver for BUTTON1 (pulled up).
// =============================================================================

#ifndef __DRIVERS__IN__BUTTON1_H
#define __DRIVERS__IN__BUTTON1_H

#include "cpu/avr/gpio.h"
#include <stdint.h>


inline void button1__init(void) {
    USE_AS_INPUT(BUTTON1);
    ENABLE_PULLUP(BUTTON1);
}

inline uint8_t button1__get(void) {
//    return IN(BUTTON1) & SIGNAL_MASK(BUTTON1);
    return IS_1(BUTTON1);
}


#endif