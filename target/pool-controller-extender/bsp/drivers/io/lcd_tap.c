// =============================================================================
// Watcher for LCDs based on HD44780 controller.
// =============================================================================

#include "drivers/io/lcd_tap.h"
#include "cpu/avr/asm.h"
#include "cpu/avr/gpio.h"


#ifdef LCD_TAP__VALUE__REG
    register uint8_t lcd_tap__value asm(QUOTE(LCD_TAP__VALUE__REG));
#endif


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
#ifndef LCD_TAP__VALUE__REG
    uint8_t lcd_tap__value;
#endif

    __IN(lcd_tap__value, PIN_REG(LCD_TAP__PORT));
    lcd_tap__on_event(lcd_tap__value);
}
