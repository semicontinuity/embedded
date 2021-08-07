// =============================================================================
// Firmware for Button LED Matrix board (16 WS2812 LEDs + 16 buttons).
// Communication with the board is performed via I2C interface.
// I2C writes: see protocol.txt.
// I2C reads must read 1 byte; returned byte is the latest keyboard event, or 0.
// =============================================================================

#include "twi_slave__handler.h"

#include <util/delay.h>
#include <cpu/avr/twi.h>
#include <avr/interrupt.h>
#include <services/tracer.h>


// application
// ---------------------------------------------------------------------------------------------------------------------

void application__init(void) {
    tracer__init();

    twi__slave_address__set(TWI__SLAVE__ADDRESS);
}


void application__start(void) {
    tracer__start();

    twi__slave__start();
}

// TWI Slave callbacks
// -----------------------------------------------------------------------------

void twi__slave__on_data_byte_requested(void) {
    __asm__ __volatile__("twi__slave__on_data_byte_requested:");
    twi__data__set(0x00);
    twi__continue(false /*true*/ , false);
}

void twi__slave__on_data_reception_started(void) {
    __asm__ __volatile__("twi__slave__on_data_reception_started:");
    twi__continue(true, false);
}

void twi__slave__on_data_byte_received(const uint8_t value) {
    __asm__ __volatile__("twi__slave__on_data_byte_received:");
    twi__continue(true, false);
}

void twi__slave__on_data_reception_finished(void) {
    __asm__ __volatile__("twi__slave__on_data_reception_finished:");
    twi__continue(true, false);
}

// main
// ---------------------------------------------------------------------------------------------------------------------

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
        // could be in interrupt to reduce latency - but interrupt handler would be big, with lots of registers to save
        if (twi__slave__handler__is_runnable()) {
            twi__slave__handler__run();
        }
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
