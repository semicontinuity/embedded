// =============================================================================
// Debug LED (at pin D5) driver.
// =============================================================================

#ifndef __DRIVERS__OUT__DEBUG_LED_D5_H
#define __DRIVERS__OUT__DEBUG_LED_D5_H

#include <stdbool.h>
#include <stdint.h>
#include "cpu/avr/gpio.h"


/**
 * Toggle Debug LED D5.
 */
inline void debug_led_d5__toggle(void) {
    TOGGLE(OUT__DEBUG_LED_D5);
}


/**
 * Set Debug LED D5 value.
 */
inline void debug_led_d5__set(const uint8_t value) {
    if (value)
        OUT_1(OUT__DEBUG_LED_D5);
    else
        OUT_0(OUT__DEBUG_LED_D5);
}


/**
 * Initialize Debug LED D5 line driver.
 */
inline void debug_led_d5__init(void) {
    USE_AS_OUTPUT(OUT__DEBUG_LED_D5);
}

#endif