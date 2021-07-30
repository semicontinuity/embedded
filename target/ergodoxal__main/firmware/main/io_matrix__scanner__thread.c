// I/O matrix scanner: handles reading of buttons in the I/O matrix.
//
// Input data rows must be on the same port (IO_MATRIX__IN__PORT).
// Column selection lines can be on any port pin.
// Column is selected by issuing logical 0; pressed rows are those that read 0 (pull-ups enabled on row pins)
//
// This thread is executed very often.
// For this reason is optimized to use only the minimal number of hand-picked registers,
// that are not used by in other threads.
// This way, it's possible to have very lightweight context switching (without lots of push-pop operations)
// ---------------------------------------------------------------------------------------------------------------------
#include "io_matrix__scanner__thread.h"

#include <stdint.h>
#include <cpu/avr/util/vthreads.h>
#include <cpu/avr/asm.h>

#include "cpu/avr/drivers/io_matrix/io_matrix__in.h"
#include "drivers/io_matrix__out_columns.h"

#include <services/tracer.h>
#include <cpu/avr/usart0.h>


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

        io_matrix__in__column0__state__update();
        io_matrix__out__column0__set(1);
        io_matrix__out__column1__set(0);
        VT_Z_YIELD_WITH_MARK_RETI(io_matrix__scanner__thread, io_matrix__scanner__thread__ip, COLUMN1_STABLE);


        io_matrix__in__column1__state__update();
        io_matrix__out__column1__set(1);
        io_matrix__out__column2__set(0);
        VT_Z_YIELD_WITH_MARK_RETI(io_matrix__scanner__thread, io_matrix__scanner__thread__ip, COLUMN2_STABLE);


        io_matrix__in__column2__state__update();
        io_matrix__out__column2__set(1);
        io_matrix__out__column3__set(0);
        VT_Z_YIELD_WITH_MARK_RETI(io_matrix__scanner__thread, io_matrix__scanner__thread__ip, COLUMN3_STABLE);


        io_matrix__in__column3__state__update();
        io_matrix__out__column3__set(1);
        io_matrix__out__column4__set(0);
        VT_Z_YIELD_WITH_MARK_RETI(io_matrix__scanner__thread, io_matrix__scanner__thread__ip, COLUMN4_STABLE);


        io_matrix__in__column4__state__update();
        io_matrix__out__column4__set(1);
        io_matrix__out__column5__set(0);
        VT_Z_YIELD_WITH_MARK_RETI(io_matrix__scanner__thread, io_matrix__scanner__thread__ip, COLUMN5_STABLE);


        io_matrix__in__column5__state__update();
        io_matrix__out__column5__set(1);
        io_matrix__out__column6__set(0);
        VT_Z_YIELD_WITH_MARK_RETI(io_matrix__scanner__thread, io_matrix__scanner__thread__ip, COLUMN6_STABLE);


        io_matrix__in__column6__state__update();
        io_matrix__out__column6__set(1);
        io_matrix__out__column0__set(0);
        VT_Z_GOTO_RETI(io_matrix__scanner__thread, io_matrix__scanner__thread__ip, BEGIN);
    }
}
