// =============================================================================
// Watcher for LCDs based on HD44780 controller.
// =============================================================================

#ifndef __HD44780_WATCHER_H
#define __HD44780_WATCHER_H

#include "cpu/avr/gpio.h"
#include <stdint.h>


/**
 * Initialize HD44780 watcher.
 */
inline void hd44780_watcher__init(void) {
    // Do nothing, assume that pins are inputs on startup
}

/**
 * Called when high-to-low transition is detected on the clock (E) line of the LCD.
 */
void hd44780_watcher__on_clock(void);


#endif