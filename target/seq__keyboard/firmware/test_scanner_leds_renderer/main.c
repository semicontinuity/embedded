// =============================================================================
// Test scanning: renders 1-bit colors on LEDS from raw data (1 byte per column)
// Column is selected for 1/4 ms = 256*8 clocks; thus timer0_ovf prescaler 8.
// =============================================================================

#include <avr/interrupt.h>
#include "cpu/avr/util/vthreads.h"
#include "cpu/avr/drivers/io_matrix/io_matrix__scanner__thread__timer.h"
#include "drivers/io_matrix__out_columns.h"
#include "drivers/io_matrix__out_rows.h"
#include "util/delay.h"
#include "data.h"
#include "io_matrix__scanner__thread.h"


// application
// -----------------------------------------------------------------------------

void application__init(void) {
    data__leds[0] = 0b10010001;
    data__leds[1] = 0b01001001;
    data__leds[2] = 0b00100101;
    data__leds[3] = 0b11111101;

    io_matrix__out_rows__init();
    io_matrix__out_columns__init();
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
