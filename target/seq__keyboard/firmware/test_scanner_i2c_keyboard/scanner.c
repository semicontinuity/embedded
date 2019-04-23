// I/O matrix scanner: handles rendering of LED colors and reading of buttons in the I/O matrix.
//
// Input data rows (switches, encoders) must be on the same port (IO_MATRIX__IN__PORT).
// Output data rows (LEDs) must be on the same port (IO_MATRIX__OUT__ROWS__PORT).
// Column selection lines can be on any port pin.
// ---------------------------------------------------------------------------------------------------------------------
#include "scanner.h"

#include <stdint.h>
#include <cpu/avr/util/vthreads.h>
#include <cpu/avr/asm.h>

#include "drivers/io_matrix__in.h"
#include "drivers/io_matrix__out_columns.h"
#include "drivers/io_matrix__out_rows.h"

#include "data.h"


// I/O matrix scanner thread
// ---------------------------------------------------------------------------------------------------------------------


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

        io_matrix__out__column3__set(0);
        io_matrix__out__column0__set(1);
        io_matrix__out_rows__set(data__leds[0]);

        VT_Z_YIELD_WITH_MARK_RETI(scanner__thread, scanner__thread__ip, COLUMN0_READ);
        io_matrix__in__column0__state__update();
        VT_Z_YIELD_WITH_MARK_RETI(scanner__thread, scanner__thread__ip, COLUMN1);


        io_matrix__out__column0__set(0);
        io_matrix__out__column1__set(1);
        io_matrix__out_rows__set(data__leds[1]);

        VT_Z_YIELD_WITH_MARK_RETI(scanner__thread, scanner__thread__ip, COLUMN1_READ);
        io_matrix__in__column1__state__update();
        VT_Z_YIELD_WITH_MARK_RETI(scanner__thread, scanner__thread__ip, COLUMN2);


        io_matrix__out__column1__set(0);
        io_matrix__out__column2__set(1);
        io_matrix__out_rows__set(data__leds[2]);

        VT_Z_YIELD_WITH_MARK_RETI(scanner__thread, scanner__thread__ip, COLUMN2_READ);
        io_matrix__in__column2__state__update();
        VT_Z_YIELD_WITH_MARK_RETI(scanner__thread, scanner__thread__ip, COLUMN3);


        io_matrix__out__column2__set(0);
        io_matrix__out__column3__set(1);
        io_matrix__out_rows__set(data__leds[3]);

        VT_Z_YIELD_WITH_MARK_RETI(scanner__thread, scanner__thread__ip, COLUMN3_READ);
        io_matrix__in__column3__state__update();
        VT_Z_GOTO_RETI(scanner__thread, scanner__thread__ip, BEGIN);
    }
}
