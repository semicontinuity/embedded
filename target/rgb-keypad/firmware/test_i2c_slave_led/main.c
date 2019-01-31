// =============================================================================
// I2C slave test - blinking LED.
// =============================================================================

#include <cpu/avr/twi.h>
#include "drivers/twi_slave.h"


void application__init(void) {
    twi_slave__thread__init();
}

void application__start(void) {
    twi__slave__start(false);
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
        if (twi_slave__thread__is_runnable()) {
            twi_slave__thread__run();
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
