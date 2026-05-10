// =============================================================================
// LED5 driver.
// =============================================================================

#ifndef __DRIVERS__OUT__LED5_H
#define __DRIVERS__OUT__LED5_H

#include <stdbool.h>
#include <stdint.h>
#include "cpu/avr/gpio.h"


/**
 * Set LED5 line value.
 */
inline void led5__set(const uint8_t value) {
    if (value)
        OUT_1(OUT__LED5);
    else
        OUT_0(OUT__LED5);
}


/**
 * Initialize the LED5 line driver.
 */
inline void led5__init(void) {
    USE_AS_OUTPUT(OUT__LED5);
}

#endif