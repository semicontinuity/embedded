// =============================================================================
// The driver for BUTTON2 (pulled up).
// =============================================================================

#ifndef __DRIVERS__IN__BUTTON2_H
#define __DRIVERS__IN__BUTTON2_H

#include "cpu/avr/gpio.h"
#include <stdint.h>


inline void button2__init(void) {
    USE_AS_INPUT(BUTTON2);
    ENABLE_PULLUP(BUTTON2);
}

inline uint8_t button2__get(void) {
    return IN(BUTTON2) & SIGNAL_MASK(BUTTON2);
}


#endif