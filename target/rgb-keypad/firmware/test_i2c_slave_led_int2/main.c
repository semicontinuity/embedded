// =============================================================================
// I2C slave test.
// =============================================================================

#include <cpu/avr/twi.h>
#include "drivers/twi_slave.h"
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

    PORTC |= ((1<<PINC4) | (1<<PINC5));
    TWDR = 0x00;            // Default Initial Value

    twi__slave_address__set(1);
    twi__slave__thread__init();
}

void application__start(void) {
    tx_ring_buffer__start();
    usart0__tx__start();

    twi__slave__thread__start();
    sei();
}

void twi__slave__on_data_byte_received(const uint8_t value) {

}

void twi__slave__on_data_reception_finished(void) {
}

void twi__slave__on_data_reception_aborted(void) {
}

ISR(TWI_vect) {
    twi__slave__thread__run();
}


// main
// -----------------------------------------------------------------------------
int main(void) __attribute__ ((naked));
int main(void) {
    application__init();
    application__start();

    _delay_ms(500);

    cli();
    if (tx_ring_buffer__is_writable()) {
        tx_ring_buffer__put('>');
    }
    if (tx_ring_buffer__is_writable()) {
        tx_ring_buffer__put('\r');
    }
    if (tx_ring_buffer__is_writable()) {
        tx_ring_buffer__put('\n');
    }
    sei();


#if !defined(__AVR_ARCH__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif
    for(;;) {
        led1__toggle();
        _delay_ms(1000);

        led1__toggle();
        _delay_ms(1000);
//        if (twi__slave__thread__is_runnable()) {
//        }
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
