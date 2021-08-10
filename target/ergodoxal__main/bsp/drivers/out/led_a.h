// =============================================================================
// LED A driver.
// =============================================================================

#ifndef __DRIVERS__OUT__LED_A_H
#define __DRIVERS__OUT__LED_A_H

#include <stdbool.h>
#include <stdint.h>
#include "cpu/avr/gpio.h"
#include <cpu/avr/asm.h>


/**
 * Toggle LED A.
 */
inline void led_a__toggle(void) {
    TOGGLE(OUT__LED_A);
}


/**
 * Set LED A value.
 */
inline void led_a__set(const uint8_t value) {
    if (value)
        OUT_1(OUT__LED_A);
    else
        OUT_0(OUT__LED_A);
}


/**
 * Copy LED A bit value from the specified bit of the supplied argument.
 */
inline void led_a__copy(const uint8_t value, const uint8_t bit) {
    OUT_BIT(SIGNAL_PORT_REG(OUT__LED_A), SIGNAL_PIN(OUT__LED_A), value, bit);
}


/**
 * Initialize LED A line driver.
 */
inline void led_a__init(void) {
    __asm__ __volatile__("led_a__init:");
    USE_AS_OUTPUT(OUT__LED_A);
}

#endif