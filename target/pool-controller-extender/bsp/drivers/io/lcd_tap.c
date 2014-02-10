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
    uint8_t portValue = PORT_VALUE(LCD_TAP);
    portValue = __builtin_avr_insert_bits(
        avr_insert_bits_map(
            0xF,
            0xF,
            LCD_TAP__RW__PIN,
            LCD_TAP__RES__PIN,
            LCD_TAP__DATA__PIN + 3,
            LCD_TAP__DATA__PIN + 2,
            LCD_TAP__DATA__PIN + 1,
            LCD_TAP__DATA__PIN + 0),
        portValue,
        0
    );
    lcd_tap__on_event(portValue);
}
