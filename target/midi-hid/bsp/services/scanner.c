// =============================================================================
// Scanner.
// =============================================================================

#include "cpu/avr/util/vthreads.h"
#include "drivers/out/columns.h"
#include "drivers/out/leds_rows.h"
#include "drivers/scanner__thread__timer.h"
#include "services/scanner__rgb_leds.h"



void scanner__button_leds__init(void) {
    buttons__leds_row__init();
}



#ifdef SCANNER__THREAD__IP__REG
register uint8_t *scanner__thread__ip asm(QUOTE(SCANNER__THREAD__IP__REG));
#else
volatile uint8_t *scanner__thread__ip;
#endif

void scanner__thread__init(void) {
    VT_INIT(scanner__thread, scanner__thread__ip);
}


void scanner__render_column(void) {
    scanner__rgb_leds__render_column();
}


void scanner__rewind(void) {
    scanner__rgb_leds__rewind();
}


void scanner__thread__run(void) {
    VT_BEGIN(scanner__thread, scanner__thread__ip);

            column3__set(0);
            column0__set(1);
            scanner__render_column();

            VT_YIELD_WITH_MARK(scanner__thread, scanner__thread__ip, column1);

            column0__set(0);
            column1__set(1);
            scanner__render_column();

            VT_YIELD_WITH_MARK(scanner__thread, scanner__thread__ip, column2);

            column1__set(0);
            column2__set(1);
            scanner__render_column();

            VT_YIELD_WITH_MARK(scanner__thread, scanner__thread__ip, column3);

            column2__set(0);
            column3__set(1);
            scanner__render_column();

            scanner__rewind();
            VT_GOTO(scanner__thread, scanner__thread__ip, BEGIN);

    VT_UNREACHEABLE_END(scanner__thread);
}


void scanner__init(void) {
    scanner__rgb_leds__init();
    scanner__button_leds__init();

    column0__init();
    column1__init();
    column2__init();
    column3__init();

    scanner__thread__init();
    scanner__thread__timer__init();
}


void scanner__start(void) {
    scanner__thread__timer__start();
}
