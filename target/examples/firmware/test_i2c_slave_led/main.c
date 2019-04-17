// =============================================================================
// I2C slave test - blinking LED.
// =============================================================================

#include <cpu/avr/twi.h>
#include "drivers/twi_slave.h"
#include "drivers/out/led1.h"


void application__init(void) {
    led1__init();
    twi__slave_address__set(1);
    twi__slave__thread__init();
}

void application__start(void) {
    twi__slave__thread__start();
}

void twi__slave__on_data_byte_received(const uint8_t value) {
    led1__toggle();
}

void twi__slave__on_data_reception_finished(void) {
}

void twi__slave__on_data_reception_aborted(void) {
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
        if (twi__slave__thread__is_runnable()) {
            twi__slave__thread__run();
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
