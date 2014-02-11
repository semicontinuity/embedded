// =============================================================================
// Watcher for LCDs based on HD44780 controller.
// =============================================================================

#include "drivers/io/lcd_tap.h"
#include "cpu/avr/asm.h"
#include "cpu/avr/gpio.h"


/**
 * Initialize LCD tap.
 */
void lcd_tap__init(void) {
    // Do nothing, assume that pins are inputs on startup
}

/**
 * Called when high-to-low transition is detected on the clock (E) line of the LCD.
 */
void lcd_tap__on_e_pin_low(void) {
    lcd_tap__on_event(PORT_VALUE(LCD_TAP));
}
