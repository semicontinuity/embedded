// =============================================================================
// Test firmware for Ergodoxial keyboard
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
//    PORTB |= 0xC0;

    io_matrix__out_columns__init();
    io_matrix__in__init();

    usart0__init();
}

void application__start(void) {
    io_matrix__out__column0__set(0);
    io_matrix__out__column1__set(0);
    io_matrix__out__column2__set(0);
    io_matrix__out__column3__set(0);
    io_matrix__out__column4__set(0);
    io_matrix__out__column5__set(0);
    io_matrix__out__column6__set(0);

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
        _delay_ms(200);

        __asm__ __volatile__("main__loop__1:");
        uint8_t portd;
//        __IN(portd, PIND);
//        uint8_t portb;
//        __IN(portb, PINB);
//        COPY_BIT(portb, 7, portd, 3);
//        COPY_BIT(portb, 6, portd, 4);

        __IN(portd, PIN_REG(SIGNAL_PORT(IO_MATRIX__IN)))
        __IN(io_matrix__in__temp, PIN_REG(SIGNAL_PORT(IO_MATRIX__IN__ALT)));
        COPY_BIT(io_matrix__in__temp, 7, portd, IO_MATRIX__IN__ROW1__PIN);
        COPY_BIT(io_matrix__in__temp, 6, portd, IO_MATRIX__IN__ROW2__PIN);


        __asm__ __volatile__("main__loop__2:");
        usart0__out__write(portd);
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
