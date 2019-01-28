// =============================================================================
// Test for soft SPI.
// Unfinished part: based on code from nerdralph.blogspot.ca,
// but reworked not to output spurious zeroes on MOSI pin.
// Also, does not save port state in register (interrupt-unfriendly),
// and allows MOSI and SCK to be on different ports.
//
// Outputs 30 bytes to light up WS2801 LED strip (works).
// =============================================================================

#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#ifndef QUOTE
#define QUOTE__(x)                      #x
#define QUOTE_(x)                       QUOTE__(x)
#define QUOTE(x)                        QUOTE_(x)
#endif

void spi__write_unfinished(const uint8_t value) {
    __asm__ __volatile__(
        "cbi   %0, %1"          "\n\t"  // MOSI low (start from known state)

        "lsl   %4"              "\n\t"
        "ori   %4, 0x01"        "\n\t"
        "L_BIT_%=:"             "\n\t"
        "cbi   %2, %3"          "\n\t"  // CLK low
        "brvc  L_SKIPPED_%="    "\n\t"  // go to L_SKIPPED if bit 6 and 7 were different before lsl
        "sbi   %0, %1"          "\n\t"  // toggle MOSI

        "L_SKIPPED_%=:"         "\n\t"
        "lsl   %4"              "\n\t"
        "sbi   %2, %3"          "\n\t"  // CLK high
        "brne  L_BIT_%="        "\n\t"

        "cbi   %2, %3"          "\n\t"  // CLK low at the end of byte
        :
        : "I"(_SFR_IO_ADDR(/*mosiPort*/PORTC)),
          "I"(/*mosiPin*/5),
          "I"(_SFR_IO_ADDR(/*sckPort*/PORTC)),
          "I"(/*sckPin*/4),
          "d"(value)
    );
}

void spi__write(uint8_t value) {
    uint8_t i = 8;
    do {
        PORTC &= ~_BV(4);
        if (value & 0x80) PORTC |= _BV(5); else PORTC &= ~_BV(5);
        value <<= 1;
        PORTC |= _BV(4);
    }
    while (--i);
}

// main
// -----------------------------------------------------------------------------
int main(void) __attribute__ ((naked));
int main(void) {

    DDRC |= _BV(4);
    DDRC |= _BV(5);

    _delay_ms(1000);

    uint8_t i = 10;
    do {
        spi__write(100);
        spi__write(150);
        spi__write(200);
    }
    while (--i);

    cli();

#if !defined(__AVR_ARCH__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif
    for(;;) {
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
