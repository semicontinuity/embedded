// =============================================================================
// Watcher for LCDs based on HD44780 controller.
// =============================================================================

#include "drivers/pool_controller/lcd_watcher.h"
#include "cpu/avr/asm.h"
#include "cpu/avr/gpio.h"

/**
 * Called when high-to-low transition is detected on the clock (E) line of the LCD.
 */
void lcd_watcher__on_e_pin_low(void) {
    uint8_t portValue = PORT_VALUE(LCD_WATCHER);
    portValue = __builtin_avr_insert_bits(
        avr_insert_bits_map(
            0xF,
            0xF,
            LCD_WATCHER__RW__PIN,
            LCD_WATCHER__RES__PIN,
            LCD_WATCHER__DATA__PIN + 3,
            LCD_WATCHER__DATA__PIN + 2,
            LCD_WATCHER__DATA__PIN + 1,
            LCD_WATCHER__DATA__PIN + 0),
        portValue,
        0
    );
    lcd_watcher__on_event(portValue);
}
