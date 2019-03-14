// =============================================================================
// WS2812B explorer.
// =============================================================================


#include <avr/interrupt.h>
#include <stdlib.h>
#include <services/console__out.h>

#include "services/console.h"
#include "services/console__in.h"
#include "services/console_i2c_slave.h"
#include "comm.h"


// =============================================================================
// Application
// =============================================================================

void application__init(void) {
    console__init();
    console__in__init();
    console__i2c_slave__init();
    comm__init();
}

void application__start(void) {
    console__start();
    console__in__start();
    comm__start();
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
        if (console__i2c_slave__run() == EXIT_FAILURE) {
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
