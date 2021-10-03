// =============================================================================
// LED blink test
// =============================================================================

#include <led_a.h>
#include <led_b.h>
#include <util/delay.h>

// application
// -----------------------------------------------------------------------------

void application__init(void) {
    led_a__init();
    led_b__init();
}

void application__start(void) {
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
        led_a__toggle();
        led_b__toggle();
        _delay_ms(1000);
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
