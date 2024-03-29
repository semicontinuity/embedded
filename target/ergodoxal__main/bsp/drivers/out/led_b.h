// =============================================================================
// LED B driver.
// =============================================================================

#ifndef __DRIVERS__OUT__LED_B_H
#define __DRIVERS__OUT__LED_B_H

#include <stdbool.h>
#include <stdint.h>
#include "cpu/avr/gpio.h"
#include <cpu/avr/asm.h>


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
 * Copy LED B bit value from the specified bit of the supplied argument.
 */
inline void led_b__copy(const uint8_t value, const uint8_t bit) {
    OUT_BIT(SIGNAL_PORT_REG(OUT__LED_B), SIGNAL_PIN(OUT__LED_B), value, bit);
}


/**
 * Initialize LED B line driver.
 */
inline void led_b__init(void) {
    __asm__ __volatile__("led_b__init:");
    USE_AS_OUTPUT(OUT__LED_B);
}

#endif