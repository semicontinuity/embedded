// =============================================================================
// Test scanning: renders 1-bit colors on LEDS from raw data (1 byte per column)
// Column is selected for 1/4 ms = 256*8 clocks; thus timer0_ovf prescaler 8.
// =============================================================================

#include <avr/interrupt.h>
#include "cpu/avr/util/vthreads.h"
#include "drivers/scanner__thread__timer.h"
#include "drivers/out/columns.h"
#include "drivers/out/leds_rows.h"
#include "util/delay.h"
#include "data.h"


// scanner
// -----------------------------------------------------------------------------

#ifdef SCANNER__THREAD__IP__REG
register uint8_t *scanner__thread__ip asm(QUOTE(SCANNER__THREAD__IP__REG));
#else
volatile uint8_t *scanner__thread__ip;
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
        OUT(OUT__LED_ROWS, data__leds[0]);
        column0__set(1);

        VT_Z_YIELD_WITH_MARK_RETI(scanner__thread, scanner__thread__ip, COLUMN1);


        column0__set(0);
        OUT(OUT__LED_ROWS, data__leds[1]);
        column1__set(1);

        VT_Z_YIELD_WITH_MARK_RETI(scanner__thread, scanner__thread__ip, COLUMN2);


        column1__set(0);
        OUT(OUT__LED_ROWS, data__leds[2]);
        column2__set(1);

        VT_Z_YIELD_WITH_MARK_RETI(scanner__thread, scanner__thread__ip, COLUMN3);


        column2__set(0);
        OUT(OUT__LED_ROWS, data__leds[3]);
        column3__set(1);

        VT_Z_GOTO_RETI(scanner__thread, scanner__thread__ip, BEGIN);
    }
}


// application
// -----------------------------------------------------------------------------

void application__init(void) {
    data__leds[0] = 0b10010001;
    data__leds[1] = 0b01001001;
    data__leds[2] = 0b00100101;
    data__leds[3] = 0b11111101;

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