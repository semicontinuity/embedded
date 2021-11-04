// =============================================================================
// Firmware for the Just Split keyboard.
// Each keyboard half reports key events via USART.
// =============================================================================

#include <avr/interrupt.h>
#include <cpu/avr/asm.h>
#include <cpu/avr/eeprom.h>

#include <cpu/avr/drivers/io_matrix/io_matrix__scanner__thread__timer.h>
#include <cpu/avr/drivers/io_matrix/io_matrix__in.h>
#include <drivers/io_matrix/io_matrix__out_columns.h>
#include <drivers/io_matrix/io_matrix__out_rows.h>
#include "io_matrix__scanner__thread.h"

#include "cpu/avr/services/keyboard/keyboard.h"

#include "comm_usart_outbound__thread.h"

#include <services/tracer.h>
#include <services/tx_ring_buffer.h>

#include <cpu/avr/twi.h>
#include "twi_slave__handler.h"

#include "cpu/avr/usart0.h"
#include "comm_usart_inbound__thread.h"

uint8_t __attribute__((section(".eeprom"))) ee__twi__slave__address = TWI__SLAVE__ADDRESS;


// application
// -----------------------------------------------------------------------------

void application__init(void) {
    io_matrix__out_columns__init();
    io_matrix__out_rows__init();
    io_matrix__in__init();

    io_matrix__scanner__thread__init();
    io_matrix__scanner__thread__timer__init();

    keyboard__init();

//    usart0__init();

    __asm__ __volatile__("application__init__twi:");
    twi__slave_address__set(eeprom__read_byte_unchecked(&ee__twi__slave__address));
}

void application__start(void) {
    io_matrix__out_columns__start();
    io_matrix__in__start();

    io_matrix__scanner__thread__timer__start();

    tx_ring_buffer__start();

//    comm_usart_outbound__thread__start();
//    comm_usart_inbound__thread__start();

    __asm__ __volatile__("application__start__twi:");
    twi__slave__start();
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
        keyboard__run();

//        __asm__ __volatile__("main__loop__2:");
//        while (comm_usart_outbound__thread__is_runnable()) {
//            comm_usart_outbound__thread__run();
//        }
//
//        __asm__ __volatile__("main__loop__3:");
//        if (comm_usart_inbound__thread__is_runnable()) {
//            comm_usart_inbound__thread__run();
//        }

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
