// =============================================================================
// Pool controller extender - main module.
// =============================================================================

#include "main.h"
#include "drivers/io/buttons_tap.h"
#include "drivers/io/lcd_tap.h"
#include "drivers/io/leds_tap.h"
#include "services/tx_ring_buffer.h"
#include "services/buttons_scanner.h"
#include "services/leds_scanner.h"
#include "services/system_timer.h"
#include "cpu/avr/asm.h"
#include "cpu/avr/int1.h"
#include "cpu/avr/timer0.h"
#include "cpu/avr/usart0.h"
#include "cpu/avr/drivers/usart0__rx.h"
#include "cpu/avr/drivers/usart0__tx.h"
#include <avr/interrupt.h>


// =============================================================================
// Handlers
// =============================================================================

void comm__rx__on_data(const uint8_t value) {
    buttons_tap__set(value);
}

bool comm__tx__has_next(void) {
    return true; // interrupt triggered only if TX buffer is not empty
}

uint8_t comm__tx__next() {
    return tx_ring_buffer__get();
}

void comm__tx__on_done(void) {    
    // never invoked
}


/**
 * Callback for the LCD watcher.
 * Called with the state of LCD bus: data in LCD_TAP__XXX bits.
 */
void pool_controller__on_lcd_event(const uint8_t value) {
    if (tx_ring_buffer__is_writable()) {
        tx_ring_buffer__put(
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
}

void pool_controller__on_buttons_scanner_event(const uint8_t changed_pins) {
    if (tx_ring_buffer__is_writable()) {
        tx_ring_buffer__put(
            __builtin_avr_insert_bits(
                avr_insert_bits_map(
                    0xF,
                    0xF,
                    BUTTONS_TAP__PIN + 5,
                    BUTTONS_TAP__PIN + 4,
                    BUTTONS_TAP__PIN + 3,
                    BUTTONS_TAP__PIN + 2,
                    BUTTONS_TAP__PIN + 1,
                    BUTTONS_TAP__PIN + 0),
                buttons_scanner__state__get(),
                0x80
            )
        );
    }
}

void pool_controller__on_leds_scanner_event(const uint8_t changed_pins) {
    if (tx_ring_buffer__is_writable()) {
        tx_ring_buffer__put(
            __builtin_avr_insert_bits(
                avr_insert_bits_map(
                    0xF,
                    0xF,
                    0xF,
                    0xF,
                    LEDS_TAP__PIN + 2,
                    LEDS_TAP__PIN + 1,
                    LEDS_TAP__PIN + 0,
                    0xF),
                leds_scanner__state__get(),
                0x00
            )
        );
    }
}


void pool_controller__on_system_timer_event(void) {
    buttons_scanner__run();
    leds_scanner__run();
}


// =============================================================================
// Application
// =============================================================================

static void application__init(void) {
    usart0__init();

    buttons_tap__init();
    leds_tap__init();
    lcd_tap__init();

    leds_scanner__init();
    buttons_scanner__init();

    int1__init();
}

static void application__start(void) {
    tx_ring_buffer__start();
    usart0__rx__start();
    usart0__tx__start();
    int1__start();
}


// =============================================================================
// Entry point.
// =============================================================================
int main(void) {
    application__init();
    application__start();

    sei();

    // run background tasks
    for(;;) {
//        cli();
//        notifications_emitter__run();
//        sei();
    }

    return 0;
}