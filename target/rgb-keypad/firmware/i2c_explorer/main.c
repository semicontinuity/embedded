// =============================================================================
// I2C exlorer.
// =============================================================================

#include "drivers/out/led1.h"
#include <avr/interrupt.h>

#include "services/tx_ring_buffer.h"
#include "cpu/avr/usart0.h"
#include "cpu/avr/drivers/usart0__tx.h"
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

void application__init(void) {
    usart0__init();
    led1__init();
}

void application__start(void) {
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

void console__println(void) {
    console__print('\r');
    console__print('\n');
}

// main
// -----------------------------------------------------------------------------
int main(void) __attribute__ ((naked));
int main(void) {
    application__init();
    application__start();

    _delay_ms(500);
    console__print('>');
    console__println();


#if !defined(__AVR_ARCH__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif
    for(;;) {
    }
#if !defined(__AVR_ARCH__)
#pragma clang diagnostic pop
#endif

#if !defined(__AVR_ARCH__)
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"
#endif
    return 0;
#if !defined(__AVR_ARCH__)
#pragma clang diagnostic pop
#endif
}
