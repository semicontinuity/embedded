// =============================================================================
// Receives 4-byte messages via I2C with raw color data (1 byte per column)
// and renders 1-bit colors on LEDS (3 bits RGB + 3 bits RGB + 1 bit button LED)
// Column is selected for 1/4 ms = 256*8 clocks; thus timer0_ovf prescaler 8.
// =============================================================================

#include <avr/interrupt.h>
#include "cpu/avr/util/vthreads.h"
#include "util/delay.h"
#include "data.h"

#include <cpu/avr/twi.h>
#include <drivers/io_matrix__out_columns.h>
#include <drivers/io_matrix__out_rows.h>
#include <drivers/io_matrix__in.h>
#include <drivers/io_matrix__scanner__thread__timer.h>
#include "io_matrix__scanner__thread.h"

#include "twi_slave_callbacks.h"
#include "twi_slave__handler.h"

// TWI Slave callbacks
// -----------------------------------------------------------------------------

uint8_t *data__leds__ptr;

void data__leds__ptr__reset(void) {
    data__leds__ptr = data__leds;
}

void twi__slave__on_data_reception_started(void) {
    data__leds__ptr__reset();
}

void twi__slave__on_data_byte_received(const uint8_t value) {
    *data__leds__ptr++ = value;
}

void twi__slave__on_data_byte_requested(void) {
    twi__data__set(0x55);
    twi__continue(false, false);
}


// application
// -----------------------------------------------------------------------------

void application__init(void) {
    data__leds__ptr__reset();

    twi__slave_address__set(TWI__SLAVE__ADDRESS);

    io_matrix__out_columns__init();
    io_matrix__out_rows__init();

    io_matrix__scanner__thread__init();
    io_matrix__scanner__thread__timer__init();
}

void application__start(void) {
    io_matrix__scanner__thread__timer__start();
}


// main
// -----------------------------------------------------------------------------
int main(void) __attribute__ ((naked));
int main(void) {
    application__init();
    application__start();

    sei();

#if !defined(__AVR_ARCH__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif
    for(;;) {
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
