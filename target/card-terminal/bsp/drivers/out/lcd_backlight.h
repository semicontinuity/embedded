// =============================================================================
// LCD backlight driver.
// =============================================================================

#ifndef __DRIVERS__OUT__LCD_BACKLIGHT_H
#define __DRIVERS__OUT__LCD_BACKLIGHT_H

#include <stdbool.h>
#include <stdint.h>
#include "cpu/avr/gpio.h"


/**
 * Toggle LCD backlight.
 */
inline void lcd_backlight__toggle(void) {
    TOGGLE(OUT__LCD_BACKLIGHT);
}


/**
 * Turn on/off LCD backlight.
 */
inline void lcd_backlight__set(const uint8_t value) {
    if (value)
        OUT_1(OUT__LCD_BACKLIGHT);
    else
        OUT_0(OUT__LCD_BACKLIGHT);
}


/**
 * Initialize LCD backlight pin.
 */
inline void lcd_backlight__init(void) {
    USE_AS_OUTPUT(OUT__LCD_BACKLIGHT);
}

#endif