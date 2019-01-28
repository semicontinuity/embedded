// =============================================================================
// LED4 driver.
// =============================================================================

#ifndef __DRIVERS__OUT__LED4_H
#define __DRIVERS__OUT__LED4_H

#include <stdbool.h>
#include <stdint.h>
#include "cpu/avr/gpio.h"


/**
 * Set LED4 line value.
 */
inline void led4__set(const uint8_t value) {
    if (value)
        OUT_1(OUT__LED4);
    else
        OUT_0(OUT__LED4);
}


/**
 * Initialize the LED4 line driver.
 */
inline void led4__init(void) {
    USE_AS_OUTPUT(OUT__LED4);
}

#endif