// =============================================================================
// The driver for BUTTON3 (pulled up).
// =============================================================================

#ifndef __DRIVERS__IN__BUTTON3_H
#define __DRIVERS__IN__BUTTON3_H

#include "cpu/avr/gpio.h"
#include <stdint.h>


inline void button3__init(void) {
    USE_AS_INPUT(BUTTON3);
    ENABLE_PULLUP(BUTTON3);
}

inline uint8_t button3__get(void) {
    return IN(BUTTON3) & SIGNAL_MASK(BUTTON3);
}


#endif