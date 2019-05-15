// =============================================================================
// Firmware for Button LED Matrix board.
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

uint8_t __attribute__((section(".eeprom"))) ee__twi__slave__address = TWI__SLAVE__ADDRESS;


// application
// ---------------------------------------------------------------------------------------------------------------------

void application__init(void) {
    alarm__init();
    led_a__init();
    led_b__init();

    leds__init();
    keyboard__init();

    twi__slave_address__set(eeprom__read_byte_unchecked(&ee__twi__slave__address));
}


void application__start(void) {
    comm_keyboard__start();
    twi__slave__start(false);
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
        keyboard__run();

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
