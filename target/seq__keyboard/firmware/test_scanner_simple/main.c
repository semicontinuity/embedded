// =============================================================================
// Test scanning
// =============================================================================

#include <cpu/avr/util/vthreads.h>
#include "drivers/scanner__thread__timer.h"

#include "cpu/avr/util/vthreads.h"

#include "drivers/out/columns.h"
#include "drivers/out/leds_rows.h"
#include "util/delay.h"


#ifdef SCANNER__THREAD__IP__REG
register uint8_t *scanner__thread__ip asm(QUOTE(SCANNER__THREAD__IP__REG));
#else
volatile uint8_t *scanner__thread__ip;
#endif

#ifdef SCANNER__PHASE__REG
register uint8_t scanner__phase asm(QUOTE(SCANNER__PHASE__REG));
#else
volatile uint8_t scanner__phase;
#endif


void scanner__thread__init(void) {
    VT_INIT(scanner__thread, scanner__thread__ip);
}

VT_FUNC(scanner__thread__function, scanner__thread__function_attrs) {
//void scanner__thread__run(void) {

//    VT_BEGIN(scanner__thread, scanner__thread__ip);

    FC_RESUME(scanner__thread__ip);
    {
        VT_MARK(scanner__thread, BEGIN);
        VT_MARK(scanner__thread, COLUMN0);

        column3__set(0);

        led1b_row__set(0);
        led1g_row__set(0);
        led1r_row__set(1);

        led2b_row__set(1);
        led2g_row__set(1);
        led2r_row__set(0);

        column0__set(1);

        VT_Z_YIELD_WITH_MARK_RETI(scanner__thread, scanner__thread__ip, COLUMN1);


        column0__set(0);

        led1b_row__set(0);
        led1g_row__set(1);
        led1r_row__set(0);

        led2b_row__set(1);
        led2g_row__set(0);
        led2r_row__set(1);

        column1__set(1);

        VT_Z_YIELD_WITH_MARK_RETI(scanner__thread, scanner__thread__ip, COLUMN2);


        column1__set(0);

        led1b_row__set(1);
        led1g_row__set(0);
        led1r_row__set(0);

        led2b_row__set(0);
        led2g_row__set(1);
        led2r_row__set(1);

        column2__set(1);

        VT_Z_YIELD_WITH_MARK_RETI(scanner__thread, scanner__thread__ip, COLUMN3);


        column2__set(0);

        led1b_row__set(1);
        led1g_row__set(1);
        led1r_row__set(1);

        led2b_row__set(0);
        led2g_row__set(0);
        led2r_row__set(0);

        column3__set(1);

        VT_Z_GOTO_RETI(scanner__thread, scanner__thread__ip, BEGIN);
    }
}


void application__init(void) {
    led1b_row__init();
    led1g_row__init();
    led1r_row__init();

    led2b_row__init();
    led2g_row__init();
    led2r_row__init();

    column0__init();
    column1__init();
    column2__init();
    column3__init();

    scanner__thread__init();
    scanner__thread__timer__init();
}

void application__start(void) {
    scanner__thread__timer__start();
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
