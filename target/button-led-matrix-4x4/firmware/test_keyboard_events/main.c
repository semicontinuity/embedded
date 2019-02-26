// =============================================================================
// Test: report pin change interrupts to USART via ring buffer
// =============================================================================

#include <util/delay.h>
#include <avr/interrupt.h>

#include "led1.h"
#include "led2.h"
#include "led3.h"

#include "services/tx_ring_buffer.h"
#include "cpu/avr/usart0.h"
#include "cpu/avr/drivers/usart0__tx.h"

#include "keyboard__pins.h"
#include "keyboard__interrupts.h"


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


void application__init(void) {
    keyboard__pins__init();

    led1__init();
    led2__init();
    led3__init();

    usart0__init();

    keyboard__interrupts__init();
}


void application__start(void) {
    tx_ring_buffer__start();
    usart0__tx__start();
    keyboard__interrupts__start();
}


void pin_change_int0__run(void) {
    led1__toggle();
    if (tx_ring_buffer__is_writable()) {
        tx_ring_buffer__put('1');
    }
}

void pin_change_int1__run(void) {
    led2__toggle();
    if (tx_ring_buffer__is_writable()) {
        tx_ring_buffer__put('2');
    }
}

void pin_change_int2__run(void) {
    led3__toggle();
    if (tx_ring_buffer__is_writable()) {
        tx_ring_buffer__put('3');
    }
}


// main
// -----------------------------------------------------------------------------
int main(void) __attribute__ ((naked));
int main(void) {
    application__init();
    _delay_us(2);
    application__start();
    sei();

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
