// =============================================================================
// Test firmware for hubbed Corne keyboard
// All rows pulled up
// All columns driven low
// No scanning
// =============================================================================

#include <util/delay.h>
#include <avr/interrupt.h>
#include <cpu/avr/asm.h>

#include <cpu/avr/drivers/io_matrix/io_matrix__in.h>
#include <drivers/io_matrix__out_columns.h>
#include <cpu/avr/usart0__tx_polled.h>
#include "cpu/avr/usart0.h"



// application
// -----------------------------------------------------------------------------

void application__init(void) {
    io_matrix__out_columns__init();
    io_matrix__in__init();

    usart0__init();
}

void application__start(void) {
    io_matrix__out__column0__set(0);
    io_matrix__out__column1__set(0);
    io_matrix__out__column2__set(0);
    io_matrix__out__column3__set(0);

    usart0__tx__enabled__set(1);
}

#ifdef IO_MATRIX__IN__TEMP__REG
register volatile uint8_t io_matrix__in__temp asm(QUOTE(IO_MATRIX__IN__TEMP__REG));
#endif

// main
// -----------------------------------------------------------------------------
int main(void) __attribute__ ((naked));
int main(void) {
    application__init();
    application__start();


#if !defined(__AVR_ARCH__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif
    __asm__ __volatile__("main__loop:");
    for(;;) {
        _delay_ms(500);

        __asm__ __volatile__("main__loop__1:");
        usart0__out__write(PINB);
        usart0__out__write(PINC);
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
