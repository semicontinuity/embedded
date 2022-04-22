// =============================================================================
// Firmware for the Harmony keyboard.
// Each keyboard half reports key events via USART.
// =============================================================================

#include <avr/interrupt.h>
#include <cpu/avr/asm.h>
#include <cpu/avr/eeprom.h>

#include <cpu/avr/drivers/io_matrix/io_matrix__scanner__thread__timer.h>
#include <cpu/avr/drivers/io_matrix/io_matrix__in.h>
#include <drivers/io_matrix/io_matrix__out_columns.h>
#include "io_matrix__scanner__thread.h"

#include "cpu/avr/services/keyboard/keyboard.h"

#include "comm_usart_outbound__thread.h"

#include <services/tracer.h>
#include <services/gp_ring_buffer.h>

#include "cpu/avr/usart0.h"


// application
// -----------------------------------------------------------------------------

void application__init(void) {
    io_matrix__out_columns__init();
    io_matrix__in__init();

    io_matrix__scanner__thread__init();
    io_matrix__scanner__thread__timer__init();

    keyboard__init();

    usart0__init();
}

void application__start(void) {
    io_matrix__out_columns__start();
    io_matrix__in__start();

    io_matrix__scanner__thread__timer__start();

    gp_ring_buffer__start();

    comm_usart_outbound__thread__start();
}


// main
// -----------------------------------------------------------------------------
int main(void) __attribute__ ((naked));
int main(void) {
    application__init();
    application__start();

    __asm__ __volatile__("sei:");
    sei();

#if !defined(__AVR_ARCH__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif
    __asm__ __volatile__("main__loop:");
    for(;;) {
        __asm__ __volatile__("main__loop__1:");
        gp_ring_buffer__to_write_mode();
        __asm__ __volatile__("main__loop__2:");
        keyboard__run();
        __asm__ __volatile__("main__loop__3:");
        gp_ring_buffer__to_read_mode();

        __asm__ __volatile__("main__loop__4:");
        while (comm_usart_outbound__thread__is_runnable()) {
            comm_usart_outbound__thread__run();
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
