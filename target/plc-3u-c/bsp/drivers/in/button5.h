// =============================================================================
// The driver for BUTTON5 (pulled up).
// =============================================================================

#ifndef __DRIVERS__IN__BUTTON5_H
#define __DRIVERS__IN__BUTTON5_H

#include "cpu/avr/gpio.h"
#include <stdint.h>


inline void button5__init(void) {
    USE_AS_INPUT(BUTTON5);
    ENABLE_PULLUP(BUTTON5);
}

inline uint8_t button5__get(void) {
    return IN(BUTTON5) & SIGNAL_MASK(BUTTON5);
}


#endif