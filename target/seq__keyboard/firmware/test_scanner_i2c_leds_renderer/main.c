// =============================================================================
// Receives 4-byte messages via I2C with raw color data (1 byte per column)
// and renders 1-bit colors on LEDS (3 bits RGB + 3 bits RGB + 1 bit button LED)
// Column is selected for 1/4 ms = 256*8 clocks; thus timer0_ovf prescaler 8.
// =============================================================================

#include <avr/interrupt.h>
#include "util/delay.h"
#include "data.h"

#include <cpu/avr/eeprom.h>
#include <cpu/avr/twi.h>
#include <drivers/io_matrix__out_columns.h>
#include <drivers/io_matrix__out_rows.h>
#include <cpu/avr/drivers/io_matrix/io_matrix__in.h>
#include <cpu/avr/drivers/io_matrix/io_matrix__scanner__thread__timer.h>
#include "io_matrix__scanner__thread.h"

#include "twi_slave_callbacks.h"
#include "twi_slave__handler.h"

#include <drivers/out/led_a.h>
#include <drivers/out/led_b.h>


uint8_t __attribute__((section(".eeprom"))) ee__twi__slave__address = TWI__SLAVE__ADDRESS;


// TWI Slave callbacks
// -----------------------------------------------------------------------------

void twi__slave__on_data_reception_started(void) {
    __asm__ __volatile__("twi__slave__on_data_reception_started:");
    twi__continue(true, false);
    data__leds__put_position_reset();
}

void twi__slave__on_data_byte_received(const uint8_t value) {
    __asm__ __volatile__("twi__slave__on_data_byte_received:");
    twi__continue(true, false);
    data__leds__put(value);
    // TODO: check that space remains for just 1 byte and invoke twi__continue(false, false);
}

void twi__slave__on_data_byte_requested(void) {
    __asm__ __volatile__("twi__slave__on_data_byte_requested:");
    twi__data__set(0x55);
    twi__continue(false, false);
}


// application
// -----------------------------------------------------------------------------

void application__init(void) {
//    twi__slave_address__set(TWI__SLAVE__ADDRESS);
    twi__slave_address__set(eeprom__read_byte_unchecked(&ee__twi__slave__address));

    io_matrix__out_columns__init();
    io_matrix__out_rows__init();

    io_matrix__scanner__thread__init();
    io_matrix__scanner__thread__timer__init();
}

void application__start(void) {
    io_matrix__scanner__thread__timer__start();
    twi__slave__start();
}


// main
// -----------------------------------------------------------------------------
int main(void) __attribute__ ((naked));
int main(void) {
    application__init();
    application__start();

    led_a__init();
    led_b__init();

    sei();

#if !defined(__AVR_ARCH__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif
    for(;;) {
        if (twi__slave__handler__is_runnable()) {
            led_a__set(1);
            twi__slave__handler__run();
            led_a__set(0);
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
