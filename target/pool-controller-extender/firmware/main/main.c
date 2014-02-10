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
#include "cpu/avr/asm.h"
#include "cpu/avr/int0.h"
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
 * Called with the state of LCD bus: bits 0-3: data lines, bit 4: RES line, bit 5: RW line.
 */
void pool_controller__on_lcd_event(const uint8_t value) {
    if (tx_ring_buffer__is_writable()) {
        tx_ring_buffer__put(0x40 | value);
    }
}

void pool_controller__on_buttons_scanner_event(const uint8_t changed_pins) {
    if (tx_ring_buffer__is_writable()) {
        tx_ring_buffer__put(0x80 | buttons_tap__get());
    }
}

void pool_controller__on_leds_scanner_event(const uint8_t changed_pins) {
    if (tx_ring_buffer__is_writable()) {
        tx_ring_buffer__put(0xC0 | leds_tap__get());
    }
}


void system_timer__on_event(void) {
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

    int0__init();
}

static void application__start(void) {
    tx_ring_buffer__start();
    usart0__rx__start();
    usart0__tx__start();
    int0__start();
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
