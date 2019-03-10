// =============================================================================
// LED1 driver.
// =============================================================================

#ifndef __DRIVERS__OUT__LED1_H
#define __DRIVERS__OUT__LED1_H

#include <stdbool.h>
#include <stdint.h>
#include "cpu/avr/gpio.h"


/**
 * Toggle LED1.
 */
inline void led1__toggle(void) {
    TOGGLE(OUT__LED1);
}


/**
 * Set LED1 value.
 */
inline void led1__set(const uint8_t value) {
    if (value)
        OUT_1(OUT__LED1);
    else
        OUT_0(OUT__LED1);
}


/**
 * Initialize the LED1 line driver.
 */
inline void led1__init(void) {
    USE_AS_OUTPUT(OUT__LED1);
}

#endif