// =============================================================================
// LCD backlight driver.
// =============================================================================

#ifndef __DRIVERS__LCD__BACKLIGHT_H
#define __DRIVERS__LCD__BACKLIGHT_H

#include <stdbool.h>
#include <stdint.h>
#include "cpu/avr/gpio.h"


/**
 * Set LCD backlight on or off.
 */
inline void lcd__backlight__set(const uint8_t value) {
    if (value)
        OUT_1(LCD__BACKLIGHT);
    else
        OUT_0(LCD__BACKLIGHT);
}


/**
 * Initialize the LCD backlight driver.
 */
inline void lcd__backlight__init(void) {
    USE_AS_OUTPUT(LCD__BACKLIGHT);
}

#endif