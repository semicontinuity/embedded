
#include "services/console__out.h"

#include <avr/interrupt.h>
#include "cpu/avr/usart0.h"
#include "cpu/avr/drivers/usart0__tx.h"
#include "services/tx_ring_buffer.h"


void console__out__init(void) {
    usart0__tx__enabled__set(1);
}

void console__out__start(void) {
    tx_ring_buffer__start();
    usart0__tx__start();
}


void console__print(const uint8_t c) {
    cli();
    if (tx_ring_buffer__is_writable()) {
        tx_ring_buffer__put(c);
    }
    sei();
}


// =============================================================================
// Handlers
// =============================================================================

bool comm__tx__has_next(void) {
    return true; // interrupt triggered only if TX buffer is not empty
}

uint8_t comm__tx__next(void) {
    return tx_ring_buffer__get();
}

void comm__tx__on_done(void) {
    // never invoked
}
