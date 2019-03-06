// =============================================================================
// I2C explorer.
// =============================================================================

#include "drivers/out/led1.h"
#include "drivers/i2c_master.h"

#include <avr/interrupt.h>
#include <stdlib.h>

#include "services/console.h"
#include "services/console_io.h"


// =============================================================================
// Application
// =============================================================================

void application__init(void) {
    led1__init();
    console__init();
    i2c_init();
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
//    _delay_ms(500);
//    console__print('>');
//    console__println();


#if !defined(__AVR_ARCH__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif
    for(;;) {
        console__read_line();
        if (console__io__run() == EXIT_FAILURE) {
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
