// =============================================================================
// Watcher for LCDs based on HD44780 controller.
// =============================================================================

#ifndef __DRIVERS__IO__LCD_TAP_H
#define __DRIVERS__IO__LCD_TAP_H

#include "cpu/avr/gpio.h"
#include <stdint.h>


/**
 * Initialize LCD tap.
 */
void lcd_tap__init(void);

/**
 * Called when high-to-low transition is detected on the clock (E) line of the LCD.
 */
void lcd_tap__on_e_pin_low(void);

/**
 * Callback to be implemented by user.
 * Called with the state of the bus: bits 0-3: data lines, bit 4: RES line, bit 5: RW line.
 */
void lcd_tap__on_event(const uint8_t event);

#endif
