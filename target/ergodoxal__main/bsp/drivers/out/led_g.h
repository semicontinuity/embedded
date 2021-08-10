// =============================================================================
// LED G driver.
// =============================================================================

#ifndef __DRIVERS__OUT__LED_G_H
#define __DRIVERS__OUT__LED_G_H

#include <stdbool.h>
#include <stdint.h>
#include "cpu/avr/gpio.h"
#include <cpu/avr/asm.h>


/**
 * Toggle LED G.
 */
inline void led_g__toggle(void) {
    TOGGLE(OUT__LED_G);
}


/**
 * Set LED G value.
 */
inline void led_g__set(const uint8_t value) {
    if (value)
        OUT_1(OUT__LED_G);
    else
        OUT_0(OUT__LED_G);
}


/**
 * Copy LED G bit value from the specified bit of the supplied argument.
 */
inline void led_g__copy(const uint8_t value, const uint8_t bit) {
    OUT_BIT(SIGNAL_PORT_REG(OUT__LED_G), SIGNAL_PIN(OUT__LED_G), value, bit);
}


/**
 * Initialize LED G line driver.
 */
inline void led_g__init(void) {
    __asm__ __volatile__("led_g__init:");
    USE_AS_OUTPUT(OUT__LED_G);
}

#endif