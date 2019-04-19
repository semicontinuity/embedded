// scanner thread
// -----------------------------------------------------------------------------

#include <stdint.h>
#include <cpu/avr/util/vthreads.h>
#include <drivers/out/columns.h>
#include "scanner__thread.h"
#include "data.h"


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
        column0__set(1);
        OUT(OUT__LED_ROWS, data__leds[0]);

        VT_Z_YIELD_WITH_MARK_RETI(scanner__thread, scanner__thread__ip, COLUMN0_READ);
        data__leds[0] = IN(IN__BUTTONS);
        VT_Z_YIELD_WITH_MARK_RETI(scanner__thread, scanner__thread__ip, COLUMN1);


        column0__set(0);
        column1__set(1);
        OUT(OUT__LED_ROWS, data__leds[1]);

        VT_Z_YIELD_WITH_MARK_RETI(scanner__thread, scanner__thread__ip, COLUMN1_READ);
        data__leds[1] = IN(IN__BUTTONS);
        VT_Z_YIELD_WITH_MARK_RETI(scanner__thread, scanner__thread__ip, COLUMN2);


        column1__set(0);
        column2__set(1);
        OUT(OUT__LED_ROWS, data__leds[2]);

        VT_Z_YIELD_WITH_MARK_RETI(scanner__thread, scanner__thread__ip, COLUMN2_READ);
        data__leds[2] = IN(IN__BUTTONS);
        VT_Z_YIELD_WITH_MARK_RETI(scanner__thread, scanner__thread__ip, COLUMN3);


        column2__set(0);
        column3__set(1);
        OUT(OUT__LED_ROWS, data__leds[3]);

        VT_Z_YIELD_WITH_MARK_RETI(scanner__thread, scanner__thread__ip, COLUMN3_READ);
        data__leds[3] = IN(IN__BUTTONS);
        VT_Z_GOTO_RETI(scanner__thread, scanner__thread__ip, BEGIN);
    }
}
