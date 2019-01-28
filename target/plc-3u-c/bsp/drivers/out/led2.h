// =============================================================================
// LED2 driver.
// =============================================================================

#ifndef __DRIVERS__OUT__LED2_H
#define __DRIVERS__OUT__LED2_H

#include <stdbool.h>
#include <stdint.h>
#include "cpu/avr/gpio.h"


/**
 * Set LED2 line value.
 */
inline void led2__set(const uint8_t value) {
    if (value)
        OUT_1(OUT__LED2);
    else
        OUT_0(OUT__LED2);
}


/**
 * Initialize the LED2 line driver.
 */
inline void led2__init(void) {
    USE_AS_OUTPUT(OUT__LED2);
}

#endif