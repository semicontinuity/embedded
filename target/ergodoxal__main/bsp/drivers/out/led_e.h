// =============================================================================
// LED E driver.
// =============================================================================

#ifndef __DRIVERS__OUT__LED_E_H
#define __DRIVERS__OUT__LED_E_H

#include <stdbool.h>
#include <stdint.h>
#include "cpu/avr/gpio.h"
#include <cpu/avr/asm.h>


/**
 * Toggle LED E.
 */
inline void led_e__toggle(void) {
    TOGGLE(OUT__LED_E);
}


/**
 * Set LED E value.
 */
inline void led_e__set(const uint8_t value) {
    if (value)
        OUT_1(OUT__LED_E);
    else
        OUT_0(OUT__LED_E);
}


/**
 * Copy LED E bit value from the specified bit of the supplied argument.
 */
inline void led_e__copy(const uint8_t value, const uint8_t bit) {
    OUT_BIT(SIGNAL_PORT_REG(OUT__LED_E), SIGNAL_PIN(OUT__LED_E), value, bit);
}


/**
 * Initialize LED E line driver.
 */
inline void led_e__init(void) {
    __asm__ __volatile__("led_e__init:");
    USE_AS_OUTPUT(OUT__LED_E);
}

#endif