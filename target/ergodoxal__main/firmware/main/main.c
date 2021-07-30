// =============================================================================
// Column is selected for 1/4 ms = 256*8 clocks; thus timer0_ovf prescaler 8.
// =============================================================================

#include <avr/interrupt.h>
#include <cpu/avr/asm.h>
#include <cpu/avr/eeprom.h>

#include <cpu/avr/drivers/io_matrix/io_matrix__scanner__thread__timer.h>
#include <cpu/avr/drivers/io_matrix/io_matrix__in.h>
#include <drivers/io_matrix__out_columns.h>
#include "io_matrix__scanner__thread.h"

#include "cpu/avr/services/keyboard/keyboard.h"

#include "comm_keyboard.h"

#include <drivers/out/led_a.h>
#include <drivers/out/led_b.h>
#include <drivers/out/led_c.h>
#include <services/tracer.h>

#include "cpu/avr/usart0.h"


// application
// -----------------------------------------------------------------------------

void application__init(void) {
    io_matrix__out_columns__init();
    io_matrix__in__init();

    io_matrix__scanner__thread__init();
    io_matrix__scanner__thread__timer__init();

    keyboard__init();

    led_a__init();
    led_b__init();
    led_c__init();

    usart0__init();
}

void application__start(void) {
    io_matrix__in__start();
    io_matrix__scanner__thread__timer__start();
    comm_keyboard__start();
    comm_keyboard__thread__start();
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
        keyboard__run();

        while (comm_keyboard__thread__is_runnable()) {
            comm_keyboard__thread__run();
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
