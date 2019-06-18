// =====================================================================================================================
// Test I/O matrix scanning, transmitting via TWI the state of scanned I/O matrix column
// =====================================================================================================================
#include <cpu/avr/asm.h>

#include "data.h"

#include "drivers/io_matrix__scanner__thread__timer.h"
#include "cpu/avr/drivers/io_matrix/io_matrix__in.h"
#include "drivers/io_matrix__out_rows.h"
#include "drivers/io_matrix__out_columns.h"
#include "io_matrix__scanner__thread.h"

#include "I2CSlave.h"
#include "comm.h"


// comm callbacks
// -----------------------------------------------------------------------------

void twi__slave__on_data_byte_requested(void) {
    I2C_transmitByte(io_matrix__in__column0__state__get());
}

void twi__slave__on_data_transmission_finished(void) {
}

void twi__slave__on_data_byte_received(const uint8_t value) {
}

void twi__slave__on_data_reception_finished(void) {
}

void twi__slave__on_data_reception_aborted(void) {
}


// application
// -----------------------------------------------------------------------------

void application__init(void) {
    io_matrix__out_columns__init();
    io_matrix__out_rows__init();
    io_matrix__in__init();

    comm__init();

    io_matrix__scanner__thread__init();
    io_matrix__scanner__thread__timer__init();
}

void application__start(void) {
    comm__start();
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
