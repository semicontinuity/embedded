// =============================================================================
// I2C explorer.
// =============================================================================

#include "drivers/out/led1.h"
#include "drivers/out/led2.h"
#include "drivers/out/led3.h"
#include "drivers/out/led4.h"

#include <avr/interrupt.h>
#include <stdlib.h>

#include "util/delay.h"

#include "services/console.h"
#include "services/console_i2c.h"


// =============================================================================
// Application
// =============================================================================

void application__init(void) {
    led1__init();
    led2__init();
    led3__init();
    led4__init();


    led1__set(1);
    led2__set(1);
    led3__set(1);
    led4__set(1);
    _delay_ms(250);
    led1__set(0);
    led2__set(0);
    led3__set(0);
    led4__set(0);

    console__init();
    console__i2c__init();
}

void application__start(void) {
    console__start();
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
        console__read_line();

        led1__set(1);
        uint8_t result = console__i2c__run();
        led1__set(0);

        if (result == EXIT_FAILURE) {
            console__print_error();
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
