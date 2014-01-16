// =============================================================================
// Watcher for LCDs based on HD44780 controller.
// =============================================================================

#include "drivers/pool_controller/lcd_watcher.h"
#include "cpu/avr/gpio.h"

/**
 * Called when high-to-low transition is detected on the clock (E) line of the LCD.
 */
void lcd_watcher__on_e_pin_low(void) {
    lcd_watcher__on_event(0);
}
