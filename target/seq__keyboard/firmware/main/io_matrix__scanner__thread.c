// I/O matrix scanner: handles rendering of LED colors and reading of buttons in the I/O matrix.
//
// Input data rows (switches, encoders) must be on the same port (IO_MATRIX__IN__PORT).
// Output data rows (LEDs) must be on the same port (IO_MATRIX__OUT__ROWS__PORT).
// Column selection lines can be on any port pin.
// ---------------------------------------------------------------------------------------------------------------------
#include "io_matrix__scanner__thread.h"

#include <stdint.h>
#include <cpu/avr/util/vthreads.h>
#include <cpu/avr/asm.h>

#include "drivers/io_matrix__in.h"
#include "drivers/io_matrix__out_columns.h"
#include "drivers/io_matrix__out_rows.h"

#include "data.h"


#ifdef IO_MATRIX__SCANNER__THREAD__IP__REG
register uint8_t *io_matrix__scanner__thread__ip asm(QUOTE(IO_MATRIX__SCANNER__THREAD__IP__REG));
#else
volatile uint8_t *io_matrix__scanner__thread__ip;
#endif


void io_matrix__scanner__thread__init(void) {
    VT_INIT(io_matrix__scanner__thread, io_matrix__scanner__thread__ip);
}


VT_FUNC(io_matrix__scanner__thread__function, io_matrix__scanner__thread__function_attrs) {
    FC_RESUME(io_matrix__scanner__thread__ip);
    {
        VT_MARK(io_matrix__scanner__thread, BEGIN);
        VT_MARK(io_matrix__scanner__thread, COLUMN0);

        io_matrix__out__column3__set(0);
        io_matrix__out__column0__set(1);
        io_matrix__out_rows__set(data__leds[0]);
        VT_Z_YIELD_WITH_MARK_RETI(io_matrix__scanner__thread, io_matrix__scanner__thread__ip, COLUMN0_BLANK);
        io_matrix__out_rows__set(0);
        VT_Z_YIELD_WITH_MARK_RETI(io_matrix__scanner__thread, io_matrix__scanner__thread__ip, COLUMN0_BLANK2);
        VT_Z_YIELD_WITH_MARK_RETI(io_matrix__scanner__thread, io_matrix__scanner__thread__ip, COLUMN1);


        io_matrix__out__column0__set(0);
        io_matrix__out__column1__set(1);
        io_matrix__out_rows__set(data__leds[1]);
        VT_Z_YIELD_WITH_MARK_RETI(io_matrix__scanner__thread, io_matrix__scanner__thread__ip, COLUMN1_BLANK);
        io_matrix__out_rows__set(0);
        VT_Z_YIELD_WITH_MARK_RETI(io_matrix__scanner__thread, io_matrix__scanner__thread__ip, COLUMN1_BLANK2);
        VT_Z_YIELD_WITH_MARK_RETI(io_matrix__scanner__thread, io_matrix__scanner__thread__ip, COLUMN2);


        io_matrix__out__column1__set(0);
        io_matrix__out__column2__set(1);
        io_matrix__out_rows__set(data__leds[2]);
        VT_Z_YIELD_WITH_MARK_RETI(io_matrix__scanner__thread, io_matrix__scanner__thread__ip, COLUMN2_BLANK);
        io_matrix__out_rows__set(0);
        VT_Z_YIELD_WITH_MARK_RETI(io_matrix__scanner__thread, io_matrix__scanner__thread__ip, COLUMN2_BLANK2);
        VT_Z_YIELD_WITH_MARK_RETI(io_matrix__scanner__thread, io_matrix__scanner__thread__ip, COLUMN3);


        io_matrix__out__column2__set(0);
        io_matrix__out__column3__set(1);
        io_matrix__out_rows__set(data__leds[3]);
        VT_Z_YIELD_WITH_MARK_RETI(io_matrix__scanner__thread, io_matrix__scanner__thread__ip, COLUMN3_BLANK);
        io_matrix__out_rows__set(0);
        VT_Z_YIELD_WITH_MARK_RETI(io_matrix__scanner__thread, io_matrix__scanner__thread__ip, COLUMN3_BLANK2);
        VT_Z_GOTO_RETI(io_matrix__scanner__thread, io_matrix__scanner__thread__ip, BEGIN);
    }
}
