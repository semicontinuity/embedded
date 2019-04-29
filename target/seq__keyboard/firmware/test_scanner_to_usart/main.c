// =====================================================================================================================
// Test I/O matrix scanning, transmitting via USART the state of scanned I/O matrix columns
// =====================================================================================================================
#include <cpu/avr/asm.h>

#include "data.h"

#include "drivers/io_matrix__scanner__thread__timer.h"
#include "drivers/io_matrix__in.h"
#include "drivers/io_matrix__out_rows.h"
#include "drivers/io_matrix__out_columns.h"
#include "io_matrix__scanner__thread.h"

#include "util/formatter.h"
#include "cpu/avr/usart0.h"
#include "cpu/avr/usart0__tx_polled.h"
#include <util/delay.h>
#include <avr/interrupt.h>


// console
// -----------------------------------------------------------------------------

void console__print(uint8_t c) {
    usart0__out__write(c);
}

void console__println(void) {
    console__print('\r');
    console__print('\n');
}

inline void console__print_byte_as_hex(const uint8_t value) {
    uint16_t hex = formatter__byte_to_hex_chars(value);
    console__print((uint8_t)(hex >> 8));
    console__print((uint8_t)(hex & 0xFF));
}

// application
// -----------------------------------------------------------------------------

void application__init(void) {
    io_matrix__out_columns__init();
    io_matrix__out_rows__init();
    io_matrix__in__init();

    io_matrix__scanner__thread__init();
    io_matrix__scanner__thread__timer__init();

    usart0__init();
}

void application__start(void) {
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
    for(;;) {
        __asm__ __volatile__("main__loop__c0:");
        console__print_byte_as_hex(io_matrix__in__column0__state__get());
        __asm__ __volatile__("main__loop__c1:");
        console__print_byte_as_hex(io_matrix__in__column1__state__get());
        __asm__ __volatile__("main__loop__c2:");
        console__print_byte_as_hex(io_matrix__in__column2__state__get());
        __asm__ __volatile__("main__loop__c3:");
        console__print_byte_as_hex(io_matrix__in__column3__state__get());
        __asm__ __volatile__("main__loop__rest:");
        console__println();
        _delay_ms(50);
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
