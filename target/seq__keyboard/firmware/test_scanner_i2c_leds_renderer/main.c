// =============================================================================
// Receives 4-byte messages via I2C with raw color data (1 byte per column)
// and renders 1-bit colors on LEDS (3 bits RGB + 3 bits RGB + 1 bit button LED)
// Column is selected for 1/4 ms = 256*8 clocks; thus timer0_ovf prescaler 8.
// =============================================================================

#include <avr/interrupt.h>
#include "cpu/avr/util/vthreads.h"
#include "drivers/scanner__thread__timer.h"
#include "drivers/out/columns.h"
#include "drivers/out/leds_rows.h"
#include "util/delay.h"
#include "data.h"

#include <cpu/avr/twi.h>
#include "twi_slave.h"
#include "twi_slave_callbacks.h"


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

        // -------------------------------------------------------------------------------------------------------------

        column3__set(0);
        OUT(OUT__LED_ROWS, data__leds[0]);
        column0__set(1);

        VT_Z_YIELD_WITH_MARK_RETI(scanner__thread, scanner__thread__ip, COLUMN0_BLANK);
        OUT(OUT__LED_ROWS, 0);
        VT_Z_YIELD_WITH_MARK_RETI(scanner__thread, scanner__thread__ip, COLUMN0_BLANK2);
        VT_Z_YIELD_WITH_MARK_RETI(scanner__thread, scanner__thread__ip, COLUMN1);

        // -------------------------------------------------------------------------------------------------------------

        column0__set(0);
        OUT(OUT__LED_ROWS, data__leds[1]);
        column1__set(1);

        VT_Z_YIELD_WITH_MARK_RETI(scanner__thread, scanner__thread__ip, COLUMN1_BLANK);
        OUT(OUT__LED_ROWS, 0);
        VT_Z_YIELD_WITH_MARK_RETI(scanner__thread, scanner__thread__ip, COLUMN1_BLANK2);
        VT_Z_YIELD_WITH_MARK_RETI(scanner__thread, scanner__thread__ip, COLUMN2);

        // -------------------------------------------------------------------------------------------------------------

        column1__set(0);
        OUT(OUT__LED_ROWS, data__leds[2]);
        column2__set(1);

        VT_Z_YIELD_WITH_MARK_RETI(scanner__thread, scanner__thread__ip, COLUMN2_BLANK);
        OUT(OUT__LED_ROWS, 0);
        VT_Z_YIELD_WITH_MARK_RETI(scanner__thread, scanner__thread__ip, COLUMN2_BLANK2);
        VT_Z_YIELD_WITH_MARK_RETI(scanner__thread, scanner__thread__ip, COLUMN3);

        // -------------------------------------------------------------------------------------------------------------

        column2__set(0);
        OUT(OUT__LED_ROWS, data__leds[3]);
        column3__set(1);

        VT_Z_YIELD_WITH_MARK_RETI(scanner__thread, scanner__thread__ip, COLUMN3_BLANK);
        OUT(OUT__LED_ROWS, 0);
        VT_Z_YIELD_WITH_MARK_RETI(scanner__thread, scanner__thread__ip, COLUMN3_BLANK2);
        VT_Z_GOTO_RETI(scanner__thread, scanner__thread__ip, BEGIN);
    }
}


// TWI Slave callbacks
// -----------------------------------------------------------------------------

uint8_t *data__leds__ptr;

void data__leds__ptr__reset(void) {
    data__leds__ptr = data__leds;
}

void twi__slave__on_data_byte_received(const uint8_t value) {
    *data__leds__ptr++ = value;
}

void twi__slave__on_data_reception_finished(void) {
    data__leds__ptr__reset();
}

void twi__slave__on_data_reception_aborted(void) {
    data__leds__ptr__reset();
}


// application
// -----------------------------------------------------------------------------

void application__init(void) {
    data__leds__ptr__reset();

    twi__slave_address__set(TWI__SLAVE__ADDRESS);
    twi__slave__thread__init();

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
    twi__slave__thread__start();
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
        if (twi__slave__thread__is_runnable()) {
            twi__slave__thread__run();
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
