// =============================================================================
// Light up LEDS using simple loop
// =============================================================================

#include "drivers/out/columns.h"
#include "drivers/out/leds_rows.h"
#include "util/delay.h"


void application__init(void) {
    led1b_row__init();
    led1g_row__init();
    led1r_row__init();

    led2b_row__init();
    led2g_row__init();
    led2r_row__init();

    buttons__leds_row__init();

    column0__init();
    column1__init();
    column2__init();
    column3__init();
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
        led1r_row__set(1);
        led1g_row__set(0);
        led1b_row__set(0);

        led2r_row__set(0);
        led2g_row__set(1);
        led2b_row__set(1);

        column0__set(1);
        _delay_ms(4);
        column0__set(0);


        led1r_row__set(0);
        led1g_row__set(1);
        led1b_row__set(0);

        led2r_row__set(1);
        led2g_row__set(0);
        led2b_row__set(1);

        column1__set(1);
        _delay_ms(4);
        column1__set(0);


        led1r_row__set(0);
        led1g_row__set(0);
        led1b_row__set(1);

        led2r_row__set(1);
        led2g_row__set(1);
        led2b_row__set(0);

        column2__set(1);
        _delay_ms(4);
        column2__set(0);


        led1r_row__set(1);
        led1g_row__set(1);
        led1b_row__set(1);

        led2r_row__set(0);
        led2g_row__set(0);
        led2b_row__set(0);

        column3__set(1);
        _delay_ms(4);
        column3__set(0);
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
