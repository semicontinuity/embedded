// =============================================================================
// Rotary encoder test.
// Continuously reads rotary encoder, and prints accumulated value to USART.
// =============================================================================

#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "cpu/avr/gpio.h"
#include "cpu/avr/usart0.h"
#include "cpu/avr/usart0__tx_polled.h"

#if CONCAT(0x,ROTARY_ENCODER__A__PORT) != CONCAT(0x,ROTARY_ENCODER__B__PORT)
#  error ROTARY_ENCODER__A__PORT and ROTARY_ENCODER__B__PORT must be the same!
#endif

#if ROTARY_ENCODER__A__PIN != 0
#  error ROTARY_ENCODER__A__PIN must be 0!
#endif

#if ROTARY_ENCODER__B__PIN != 1
#  error ROTARY_ENCODER__B__PIN must be 1!
#endif

void rotary_encoder__init(void) {
    USE_AS_INPUT(ROTARY_ENCODER__A);
    ENABLE_PULLUP(ROTARY_ENCODER__A);
    USE_AS_INPUT(ROTARY_ENCODER__B);
    ENABLE_PULLUP(ROTARY_ENCODER__B);
}

uint8_t rotary_encoder__step[] = {0, 0xFF, 1 ,0, 1, 0, 0, 0xFF, 0xFF, 0, 0, 1, 0, 1, 0xFF, 0};
uint8_t rotary_encoder__state = 0;

uint8_t rotary_encoder__value(void) {
  return PORT_VALUE(ROTARY_ENCODER__A) & 0x03;
}

uint8_t rotary_encoder__read(void) {
  rotary_encoder__state = (rotary_encoder__state << 2) | rotary_encoder__value();
  return rotary_encoder__step[rotary_encoder__state & 0x0F];
}


/**
 * Converts a lowe nibble of a byte hex character.
 */
uint8_t formatter__nibble_to_hex_char(uint8_t value) {
    if (value > 9) value += ('A' - ('9' + 1));
    return value + '0';
}

/**
 * Converts a byte to 2 hex characters.
 */
uint16_t formatter__byte_to_hex_chars(const uint8_t value) {
    return (formatter__nibble_to_hex_char(value >> 4) << 8) | formatter__nibble_to_hex_char(value & 0x0F);
}


void console__print_byte_as_hex(const uint8_t value) {
    uint16_t hex = formatter__byte_to_hex_chars(value);
    usart0__out__write((uint8_t)(hex >> 8));
    usart0__out__write((uint8_t)(hex & 0xFF));
}

void console__println(void) {
    usart0__out__write(10);
}


void application__init(void) {
    usart0__init();
    rotary_encoder__init();
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
    uint8_t value = 0;
    for(;;) {
        uint8_t c = rotary_encoder__read();
        if (c != 0) {
            value += c;
            console__print_byte_as_hex(value);
            console__println();
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
