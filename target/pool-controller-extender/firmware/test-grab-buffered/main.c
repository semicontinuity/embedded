// =============================================================================
// LCD tap test.
// Grab data, without checks for buffer overflow.
// =============================================================================

#include "main.h"
#include "drivers/io/lcd_tap.h"
#include "services/tx_ring_buffer.h"
#include "cpu/avr/asm.h"
#include "cpu/avr/int1.h"
#include "cpu/avr/usart0.h"
#include "cpu/avr/usart0__tx_polled.h"
#include "cpu/avr/gpio.h"
#include <avr/interrupt.h>


// =============================================================================
// Handlers
// =============================================================================

/**
 * Callback for the LCD watcher.
 * Called with the state of LCD bus: data in LCD_TAP__XXX bits.
 */
void pool_controller__on_lcd_event(const uint8_t value) {
    tx_ring_buffer__put(value);
}


// =============================================================================
// Application
// =============================================================================

static void application__init(void) {
    ENABLE_PULLUP(USART0__RX);
    usart0__init();

    lcd_tap__init();   

    // interrupt from INT1 pin, rising edge
    INT1__CONFIG__HOST = (INT1__CONFIG__HOST | (1<<ISC11) | (1<<ISC10));
}

static void application__start(void) {
    tx_ring_buffer__start();
    usart0__tx__enabled__set(1);

    int1__start();
}


// =============================================================================
// Entry point.
// =============================================================================

int main(void) {
    application__init();
    application__start();

    sei();

    for(;;) {
        usart0__out__wait();
        tx_ring_buffer__wait_until_not_at_limit();
        usart0__putc(tx_ring_buffer__get());
    }

    return 0;
}
