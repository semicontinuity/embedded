// =============================================================================
// Test firmware for Ergodoxial keyboard
// Outputs values of column state registers to USART
// =============================================================================

#include <util/delay.h>
#include <avr/interrupt.h>
#include <cpu/avr/asm.h>

#include <cpu/avr/drivers/io_matrix/io_matrix__scanner__thread__timer.h>
#include "io_matrix__scanner__thread.h"

#include <cpu/avr/drivers/io_matrix/io_matrix__in.h>
#include <drivers/io_matrix__out_columns.h>
#include <cpu/avr/usart0__tx_polled.h>
#include "cpu/avr/usart0.h"



// application
// -----------------------------------------------------------------------------

void application__init(void) {
    io_matrix__out_columns__init();
    io_matrix__in__init();

    io_matrix__scanner__thread__init();
    io_matrix__scanner__thread__timer__init();

    usart0__init();
}

void application__start(void) {
    io_matrix__out_columns__start();
    io_matrix__in__start();

    io_matrix__scanner__thread__timer__start();

    usart0__tx__enabled__set(1);
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
    __asm__ __volatile__("main__loop:");
    for(;;) {
        _delay_ms(200);

        usart0__out__write(io_matrix__in__column0__state__get() & 0xFC);
        usart0__out__write(io_matrix__in__column1__state__get() & 0xFC);
        usart0__out__write(io_matrix__in__column2__state__get() & 0xFC);
        usart0__out__write(io_matrix__in__column3__state__get() & 0xFC);
        usart0__out__write(io_matrix__in__column4__state__get() & 0xFC);
        usart0__out__write(io_matrix__in__column5__state__get() & 0xFC);
        usart0__out__write(io_matrix__in__column6__state__get() & 0xFC);
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
