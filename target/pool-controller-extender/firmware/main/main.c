// =============================================================================
// Pool controller extender - main module.
// =============================================================================

#include "drivers/buttons.h"
#include "drivers/hd44780_watcher.h"
#include "flags/notifications_pending__lcd.h"
#include "services/notifications_emitter.h"
#include "services/tx_ring_buffer.h"
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
    return false;
}

uint8_t comm__tx__next() {
    return 0;
}

void comm__tx__on_done(void) {    
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


// =============================================================================
// Application
// =============================================================================

static void application__init(void) {
    usart0__init();
    buttons__init();
    hd44780_watcher__init();
}

static void application__start(void) {
    tx_ring_buffer__start();
    notifications_pending__lcd__set(0);
    usart0__rx__start();
    usart0__tx__start();
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
