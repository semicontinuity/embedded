// =============================================================================
// Firmware for Button LED Matrix board.
// =============================================================================

#include <cpu/avr/eeprom.h>
#include <cpu/avr/asm.h>
#include "cpu/avr/services/keyboard/keyboard.h"

#include "comm.h"
#include "I2CSlave.h"
#include "drivers/comm/twi_slave_callbacks.h"

#include <drivers/out/alarm.h>
#include <drivers/out/led_a.h>
#include <drivers/out/led_b.h>

#include "leds.h"
#include "comm_keyboard.h"

#include <util/delay.h>
#include <cpu/avr/twi.h>

uint8_t __attribute__((section(".eeprom"))) ee__twi__slave__address = TWI__SLAVE__ADDRESS;


// application
// ---------------------------------------------------------------------------------------------------------------------

void application__init(void) {
    alarm__init();
    led_a__init();
    led_b__init();

    keyboard__init();

    leds__init();
    comm__init();

    twi__slave_address__set(eeprom__read_byte_unchecked(&ee__twi__slave__address));
}


void application__start(void) {
    comm_keyboard__start();
    comm__start();
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
