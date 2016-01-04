// =============================================================================
// The driver for BUTTON4 (pulled up).
// =============================================================================

#ifndef __DRIVERS__IN__BUTTON4_H
#define __DRIVERS__IN__BUTTON4_H

#include "cpu/avr/gpio.h"
#include <stdint.h>


inline void button4__init(void) {
    USE_AS_INPUT(BUTTON4);
    ENABLE_PULLUP(BUTTON4);
}

inline uint8_t button4__get(void) {
    //return IN(BUTTON4) & SIGNAL_MASK(BUTTON4);
    return IS_1(BUTTON4);
}


#endif