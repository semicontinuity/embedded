// =============================================================================
// LED B driver.
// =============================================================================

#ifndef __DRIVERS__OUT__LED_B_H
#define __DRIVERS__OUT__LED_B_H

#include <stdbool.h>
#include <stdint.h>
#include "cpu/avr/gpio.h"


/**
 * Toggle LED B.
 */
inline void led_b__toggle(void) {
    TOGGLE(OUT__LED_B);
}


/**
 * Set LED B value.
 */
inline void led_b__set(const uint8_t value) {
    if (value)
        OUT_1(OUT__LED_B);
    else
        OUT_0(OUT__LED_B);
}


/**
 * Initialize LED B line driver.
 */
inline void led_b__init(void) {
    USE_AS_OUTPUT(OUT__LED_B);
}

#endif