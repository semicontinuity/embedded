// =============================================================================
// I2C slave test - blinking LED, using interrupts.
// =============================================================================

#include <cpu/avr/twi.h>
#include "drivers/twi_slave.h"
#include "drivers/out/leds_rows.h"
#include <avr/interrupt.h>


void application__init(void) {
    PORTC |= ((1<<PINC4) | (1<<PINC5));
    TWDR = 0x00;            // Default Initial Value

    twi__slave_address__set(1);
    twi__slave__thread__init();
}

void application__start(void) {
    twi__slave__thread__start();
    sei();
}

void twi__slave__on_data_byte_received(const uint8_t value) {
}

void twi__slave__on_data_reception_finished(void) {
}

void twi__slave__on_data_reception_aborted(void) {
}

ISR(TWI_vect) {
    twi__slave__thread__run();
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
//        if (twi__slave__thread__is_runnable()) {
//        }
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
