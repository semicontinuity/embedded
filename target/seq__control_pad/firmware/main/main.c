// =============================================================================
// Receives 4-byte messages via I2C with raw color data (1 byte per column)
// and renders 1-bit colors on LEDS (3 bits RGB + 3 bits RGB + 1 bit button LED)
// Column is selected for 1/4 ms = 256*8 clocks; thus timer0_ovf prescaler 8.
// =============================================================================

#include <avr/interrupt.h>
#include <cpu/avr/asm.h>
#include <cpu/avr/eeprom.h>

#include <drivers/io_matrix__out_columns.h>
#include <drivers/io_matrix__out_rows.h>
#include <cpu/avr/drivers/io_matrix/io_matrix__in.h>
#include <cpu/avr/drivers/io_matrix/io_matrix__scanner__thread__timer.h>
#include "io_matrix__scanner__thread.h"

#include "cpu/avr/services/keyboard/keyboard.h"
#include <drivers/in/encoder0.h>
#include <drivers/in/encoder0__switch.h>

#include <cpu/avr/twi.h>
#include "twi_slave__handler.h"
#include "comm_events.h"
#include "comm_encoder.h"

#include <drivers/out/alarm.h>
#include <drivers/out/led_a.h>
#include <drivers/out/led_b.h>

#include <services/tracer.h>

//uint8_t __attribute__((section(".eeprom"))) ee__twi__slave__address = TWI__SLAVE__ADDRESS;

// no-op impl for matrix encoders
// -----------------------------------------------------------------------------

void keyboard__port_a__encoders__process(uint8_t state, uint8_t changes) {}
void keyboard__port_b__encoders__process(uint8_t state, uint8_t changes) {}
void keyboard__port_c__encoders__process(uint8_t state, uint8_t changes) {}
void keyboard__port_d__encoders__process(uint8_t state, uint8_t changes) {}

// application
// -----------------------------------------------------------------------------

void application__init(void) {
    tracer__init();

    io_matrix__out_columns__init();
    io_matrix__out_rows__init();
    io_matrix__in__init();

    io_matrix__scanner__thread__init();
    io_matrix__scanner__thread__timer__init();

    encoder0__init();
    encoder0__switch__init();
    keyboard__init();

    alarm__init();
//    led_a__init();
//    led_b__init();

    twi__slave_address__set(0x08);
}

void application__start(void) {
    tracer__start();
    io_matrix__in__start();
    io_matrix__scanner__thread__timer__start();
    comm_events__start();
    comm_encoder__start();
    twi__slave__start();
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
        keyboard__run();
        encoder0__run();
        encoder0__switch__run();
        comm_encoder__run();
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
