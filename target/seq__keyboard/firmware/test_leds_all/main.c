// =============================================================================
// LEDs scanning test.
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
    led1b_row__set(1);
    led1g_row__set(1);
    led1r_row__set(1);
    led2b_row__set(1);
    led2g_row__set(1);
    led2r_row__set(1);
}

//#define on_delay() do { _delay_ms(2); } while (0)
//#define off_delay() do { _delay_ms(6); } while (0)

//#define on_delay() do { _delay_loop_2(4096); } while (0)
//#define off_delay() do { _delay_loop_2(3*4096); } while (0)

//#define on_delay() do { _delay_loop_2(2500); } while (0)
//#define off_delay() do { _delay_loop_2(3*2500); } while (0)

//#define on_delay() do { _delay_loop_2(2048); } while (0)
//#define off_delay() do { _delay_loop_2(3*2048); } while (0)

//#define on_delay() do { _delay_loop_2(1*256); } while (0)
//#define off_delay() do { _delay_loop_2(31*256); } while (0)

//#define on_delay() do { _delay_loop_2(1*32); } while (0)
//#define off_delay() do { _delay_loop_2(255*32); } while (0)

//#define on_delay() do { _delay_ms(8); } while (0)
//#define off_delay() do {} while (0)

//#define on_delay() do { _delay_ms(4); } while (0)
//#define off_delay() do {} while (0)

#define on_delay() do { _delay_us(32); } while (0)
#define off_delay() do { _delay_ms(8); } while (0)


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
        column0__set(1);
        on_delay();
        column0__set(0);
        off_delay();

        column1__set(1);
        on_delay();
        column1__set(0);
        off_delay();

        column2__set(1);
        on_delay();
        column2__set(0);
        off_delay();

        column3__set(1);
        on_delay();
        column3__set(0);
        off_delay();
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
