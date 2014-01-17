// =============================================================================
// Pool controller extender - main module.
// =============================================================================

#include "main.h"
#include "drivers/pool_controller/buttons.h"
#include "drivers/pool_controller/lcd_watcher.h"
#include "drivers/pool_controller/leds_watcher.h"
#include "services/tx_ring_buffer.h"
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
    buttons__set(value);
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


void pool_controller__on_lcd_event(const uint8_t value) {
    if (tx_ring_buffer__is_writable()) {
        tx_ring_buffer__put(0x40 | value);
    }
}

void pool_controller__on_keypad_event(const uint8_t value) {
    if (tx_ring_buffer__is_writable()) {
        tx_ring_buffer__put(0x80 | value);
    }
}

void pool_controller__on_led_event(const uint8_t value) {
    if (tx_ring_buffer__is_writable()) {
        tx_ring_buffer__put(0xC0 | value);
    }
}


void system_timer__on_event(void) {
}


// =============================================================================
// Application
// =============================================================================

static void application__init(void) {
    usart0__init();
    buttons__init();
    leds_watcher__init();
    lcd_watcher__init();
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
