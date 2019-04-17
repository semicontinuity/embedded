// =============================================================================
// Test - send data to USART with buffering
// =============================================================================

#include "services/tx_ring_buffer.h"
#include "cpu/avr/asm.h"
#include "cpu/avr/usart0.h"
#include "cpu/avr/drivers/usart0__tx.h"
#include <avr/interrupt.h>
#include <util/delay.h>

// =============================================================================
// Handlers
// =============================================================================

bool comm__tx__has_next(void) {
    return true; // interrupt triggered only if TX buffer is not empty
}

uint8_t comm__tx__next() {
    return tx_ring_buffer__get();
}

void comm__tx__on_done(void) {
    // never invoked
}

// =============================================================================
// Application
// =============================================================================

static void application__init(void) {
    ENABLE_PULLUP(USART0__RX);
    usart0__init();
}

static void application__start(void) {
    tx_ring_buffer__start();
    usart0__tx__start();
}


// =============================================================================
// Entry point.
// =============================================================================
int main(void) {
    application__init();
    application__start();

    for(;;) {
        _delay_ms(500);
        cli();
        if (tx_ring_buffer__is_writable()) {
            tx_ring_buffer__put('H');
        }
        if (tx_ring_buffer__is_writable()) {
            tx_ring_buffer__put('e');
        }
        if (tx_ring_buffer__is_writable()) {
            tx_ring_buffer__put('l');
        }
        if (tx_ring_buffer__is_writable()) {
            tx_ring_buffer__put('l');
        }
        if (tx_ring_buffer__is_writable()) {
            tx_ring_buffer__put('o');
        }
        if (tx_ring_buffer__is_writable()) {
            tx_ring_buffer__put('!');
        }
        if (tx_ring_buffer__is_writable()) {
            tx_ring_buffer__put('\r');
        }
        if (tx_ring_buffer__is_writable()) {
            tx_ring_buffer__put('\n');
        }
        sei();
    }

    return 0;
}
