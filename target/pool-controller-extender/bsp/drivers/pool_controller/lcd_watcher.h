// =============================================================================
// Watcher for LCDs based on HD44780 controller.
// =============================================================================

#ifndef __DRIVERS__POOL_CONTROLLER__LCD_WATCHER_H
#define __DRIVERS__POOL_CONTROLLER__LCD_WATCHER_H

#include "cpu/avr/gpio.h"
#include <stdint.h>


/**
 * Initialize HD44780 watcher.
 */
inline void lcd_watcher__init(void) {
    // Do nothing, assume that pins are inputs on startup
}

/**
 * Called when high-to-low transition is detected on the clock (E) line of the LCD.
 */
void lcd_watcher__on_e_pin_low(void);

/**
 * Callback to be implemented by user.
 * Called with the state of the bus: bits 0-3: data lines, bit 4: RES line, bit 5: RW line.
 */
void lcd_watcher__on_event(const uint8_t event);

#endif