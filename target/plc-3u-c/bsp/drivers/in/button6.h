// =============================================================================
// The driver for BUTTON6 (pulled up).
// =============================================================================

#ifndef __DRIVERS__IN__BUTTON6_H
#define __DRIVERS__IN__BUTTON6_H

#include "cpu/avr/gpio.h"
#include <stdint.h>


inline void button6__init(void) {
    USE_AS_INPUT(BUTTON6);
    ENABLE_PULLUP(BUTTON6);
}

inline uint8_t button6__get(void) {
    return (IN(BUTTON6) & SIGNAL_MASK(BUTTON6));
}


#endif