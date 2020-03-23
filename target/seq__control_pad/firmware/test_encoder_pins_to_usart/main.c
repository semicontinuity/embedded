// =====================================================================================================================
// Test: continuously write to USART the value read from encoder pins
// (no USART connector on board!)
// =====================================================================================================================
#include <cpu/avr/asm.h>

#include "util/formatter.h"

#include "cpu/avr/usart0.h"
#include "cpu/avr/usart0__tx_polled.h"
#include <util/delay.h>

#include <drivers/in/encoder0__switch.h>
#include <drivers/in/encoder0.h>


void console__print(uint8_t c) {
    usart0__out__write(c);
}

void console__println(void) {
    console__print('\r');
    console__print('\n');
}

inline void console__print_byte_as_hex(const uint8_t value) {
    uint16_t hex = formatter__byte_to_hex_chars(value);
    console__print((uint8_t)(hex >> 8U));
    console__print((uint8_t)(hex & 0xFFU));
}


// application
// -----------------------------------------------------------------------------

void application__init(void) {
    encoder0__init();
    encoder0__switch__init();
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

#if !defined(__AVR_ARCH__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif
    for(;;) {
        console__print_byte_as_hex(IN(IN__ENCODER0__SWITCH));
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
