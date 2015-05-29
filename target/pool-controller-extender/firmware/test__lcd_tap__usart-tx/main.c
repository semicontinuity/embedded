// =============================================================================
// Pool controller extender test - send events via USART when LCD E pin goes low
// =============================================================================

#include "drivers/io/lcd_tap.h"
#include "cpu/avr/asm.h"
#include "cpu/avr/int1.h"
#include "cpu/avr/usart0.h"
#include "cpu/avr/usart0__tx_polled.h"
#include <avr/interrupt.h>

// =============================================================================
// Handlers
// =============================================================================

/**
 * Callback for the LCD watcher.
 * Called with the state of LCD bus: data in LCD_TAP__XXX bits.
 */
void pool_controller__on_lcd_event(const uint8_t value) {
    usart0__out__write(
            __builtin_avr_insert_bits(
                avr_insert_bits_map(
                    0xF,
                    0xF,
                    LCD_TAP__RW__PIN,
                    LCD_TAP__RES__PIN,
                    LCD_TAP__DATA__PIN + 3,
                    LCD_TAP__DATA__PIN + 2,
                    LCD_TAP__DATA__PIN + 1,
                    LCD_TAP__DATA__PIN + 0),
                value,
                0x40
            )
    );
}

// =============================================================================
// Application
// =============================================================================

static void application__init(void) {
    ENABLE_PULLUP(USART0__RX);
    usart0__init();
    lcd_tap__init();   
    int1__init();    
}

static void application__start(void) {
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
    }

    return 0;
}
