// Scanner: handles rendering of LED colors and reading of buttons in the I/O matrix
// ---------------------------------------------------------------------------------------------------------------------

#include <stdint.h>
#include <cpu/avr/util/vthreads.h>
#include <drivers/out/columns.h>
#include "scanner.h"
#include "data.h"
#include "keyboard__pins__logical.h"


#ifdef SCANNER__THREAD__IP__REG
register uint8_t *scanner__thread__ip asm(QUOTE(SCANNER__THREAD__IP__REG));
#else
volatile uint8_t *scanner__thread__ip;
#endif


void scanner__thread__init(void) {
    VT_INIT(scanner__thread, scanner__thread__ip);
}


VT_FUNC(scanner__thread__function, scanner__thread__function_attrs) {
    FC_RESUME(scanner__thread__ip);
    {
        VT_MARK(scanner__thread, BEGIN);
        VT_MARK(scanner__thread, COLUMN0);

        column3__set(0);
        column0__set(1);
        OUT(OUT__LED_ROWS, data__leds[0]);

        VT_Z_YIELD_WITH_MARK_RETI(scanner__thread, scanner__thread__ip, COLUMN0_READ);
        keyboard__pins__port_a__state__set(IN(IN__BUTTONS));
        VT_Z_YIELD_WITH_MARK_RETI(scanner__thread, scanner__thread__ip, COLUMN1);


        column0__set(0);
        column1__set(1);
        OUT(OUT__LED_ROWS, data__leds[1]);

        VT_Z_YIELD_WITH_MARK_RETI(scanner__thread, scanner__thread__ip, COLUMN1_READ);
        keyboard__pins__port_b__state__set(IN(IN__BUTTONS));
        VT_Z_YIELD_WITH_MARK_RETI(scanner__thread, scanner__thread__ip, COLUMN2);


        column1__set(0);
        column2__set(1);
        OUT(OUT__LED_ROWS, data__leds[2]);

        VT_Z_YIELD_WITH_MARK_RETI(scanner__thread, scanner__thread__ip, COLUMN2_READ);
        keyboard__pins__port_c__state__set(IN(IN__BUTTONS));
        VT_Z_YIELD_WITH_MARK_RETI(scanner__thread, scanner__thread__ip, COLUMN3);


        column2__set(0);
        column3__set(1);
        OUT(OUT__LED_ROWS, data__leds[3]);

        VT_Z_YIELD_WITH_MARK_RETI(scanner__thread, scanner__thread__ip, COLUMN3_READ);
        keyboard__pins__port_d__state__set(IN(IN__BUTTONS));
        VT_Z_GOTO_RETI(scanner__thread, scanner__thread__ip, BEGIN);
    }
}
