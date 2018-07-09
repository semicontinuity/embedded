// =============================================================================
// Debug LED (at pin D6) driver.
// =============================================================================

#ifndef __DRIVERS__OUT__DEBUG_LED_LCD_D6_H
#define __DRIVERS__OUT__DEBUG_LED_LCD_D6_H

#include <stdbool.h>
#include <stdint.h>
#include "cpu/avr/gpio.h"


/**
 * Toggle Debug LED D6.
 */
inline void debug_led_lcd_d6__toggle(void) {
    TOGGLE(OUT__DEBUG_LED_LCD_D6);
}


/**
 * Set Debug LED D6 value.
 */
inline void debug_led_lcd_d6__set(const uint8_t value) {
    if (value)
        OUT_1(OUT__DEBUG_LED_LCD_D6);
    else
        OUT_0(OUT__DEBUG_LED_LCD_D6);
}


/**
 * Initialize Debug LED D6 line driver.
 */
inline void debug_led_lcd_d6__init(void) {
    USE_AS_OUTPUT(OUT__DEBUG_LED_LCD_D6);
}

#endif