// =============================================================================
// USART to soft SPI relay.
// =============================================================================

#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "cpu/avr/gpio.h"
#include "cpu/avr/usart0.h"
#include "cpu/avr/usart0__rx_polled.h"


void soft_spi0__init(void) {
    USE_AS_OUTPUT(SOFT_SPI0__MOSI);
    USE_AS_OUTPUT(SOFT_SPI0__SCK);
}


void soft_spi0__write(uint8_t value) {
    uint8_t i = 8;
    do {
        OUT_0(SOFT_SPI0__SCK);
        if (value & 0x80) OUT_1(SOFT_SPI0__MOSI); else OUT_0(SOFT_SPI0__MOSI);
        value <<= 1;
        OUT_1(SOFT_SPI0__SCK);
    }
    while (--i);
}


void application__init(void) {
    usart0__init();
    soft_spi0__init();
}

void application__start(void) {
    usart0__rx__enabled__set(1);
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
        uint8_t c = usart0__in__read();
        soft_spi0__write(c);
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
