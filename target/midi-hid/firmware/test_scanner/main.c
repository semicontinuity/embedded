// =============================================================================
// I2C test - blinking LEDs.
// =============================================================================

#include "services/scanner.h"
#include "drivers/out/columns.h"
#include "drivers/out/leds_rows.h"
#include "util/delay.h"


void application__init(void) {
    scanner__init();
}

void application__start(void) {
    scanner__start();
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
