// =====================================================================================================================
// Test: continuosly write to USART the value read from I/O matrix input rows, when column 0 is selected
// =====================================================================================================================
#include <cpu/avr/asm.h>

#include "drivers/io_matrix__in.h"
#include "drivers/io_matrix__out_columns.h"

#include "util/formatter.h"

#include "cpu/avr/usart0.h"
#include "cpu/avr/usart0__tx_polled.h"
#include <util/delay.h>



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
    io_matrix__in__init();

    usart0__init();
}

void application__start(void) {
    usart0__tx__enabled__set(1);
}


// main
// -----------------------------------------------------------------------------

int main(void) __attribute__ ((naked));
int main(void) {
    application__init();
    application__start();

    io_matrix__out__column0__set(1);

#if !defined(__AVR_ARCH__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif
    for(;;) {
        console__print_byte_as_hex(PINB);
        console__println();
        _delay_ms(100);
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
