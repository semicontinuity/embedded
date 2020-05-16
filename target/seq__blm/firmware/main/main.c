// =============================================================================
// Firmware for Button LED Matrix board (16 WS2812 LEDs + 16 buttons).
// Communication with the board is performed via I2C interface.
// I2C writes payload is 4 bytes: {LED index, G, R, B}.
// I2C reads must read 1 bytes; returned is the latest keyboard event or 0.
// =============================================================================

#include <cpu/avr/eeprom.h>

#include <drivers/out/alarm.h>
#include <drivers/out/led_a.h>
#include <drivers/out/led_b.h>

#include "leds.h"
#include "cpu/avr/services/keyboard/keyboard.h"

#include "comm_keyboard.h"
#include "twi_slave__handler.h"

#include <util/delay.h>
#include <cpu/avr/twi.h>
#include <avr/interrupt.h>
#include <services/tracer.h>


uint8_t __attribute__((section(".eeprom"))) ee__twi__slave__address = TWI__SLAVE__ADDRESS;


void keyboard__port_b__encoders__process(uint8_t state, uint8_t changes) {}
void keyboard__port_c__encoders__process(uint8_t state, uint8_t changes) {}
void keyboard__port_d__encoders__process(uint8_t state, uint8_t changes) {}


// application
// ---------------------------------------------------------------------------------------------------------------------

void application__init(void) {
    tracer__init();

    alarm__init();
    led_a__init();
    led_b__init();

    leds__init();
//    keyboard__init();

    twi__slave_address__set(eeprom__read_byte_unchecked(&ee__twi__slave__address));
}


void application__start(void) {
    tracer__start();

    comm_keyboard__start();
    twi__slave__start();
}


// main
// ---------------------------------------------------------------------------------------------------------------------

int main(void) __attribute__ ((naked));
int main(void) {
    application__init();
    _delay_us(2);
    application__start();

    sei();

#if !defined(__AVR_ARCH__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif
    for(;;) {
        leds__run();
//        keyboard__run();

        // must be in interrupt to reduce latency
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
