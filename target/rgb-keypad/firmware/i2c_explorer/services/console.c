
#include "services/console.h"

#include <avr/interrupt.h>
#include "cpu/avr/usart0.h"
#include "cpu/avr/usart0__rx_polled.h"
#include "cpu/avr/drivers/usart0__tx.h"
#include "services/tx_ring_buffer.h"

#define CONSOLE__BUFFER_LENGTH 128

uint8_t console__input_buffer[CONSOLE__BUFFER_LENGTH];
uint16_t console__input_length;


void console__init(void) {
    usart0__init();
    usart0__tx__enabled__set(1);
    usart0__rx__enabled__set(1);
}

void console__start(void) {
    tx_ring_buffer__start();
    usart0__tx__start();
}


void console__read_line(void) {
    console__input_length = 0;
    while (1) {
        uint8_t c = usart0__in__read();

        if (c == 13 || c == 10) break;
        if (console__input_length < CONSOLE__BUFFER_LENGTH) console__input_buffer[console__input_length++] = c;
    }
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

uint8_t comm__tx__next() {
    return tx_ring_buffer__get();
}

void comm__tx__on_done(void) {
    // never invoked
}
