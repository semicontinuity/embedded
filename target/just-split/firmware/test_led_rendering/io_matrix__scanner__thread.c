// Configured to be executed about 7812 times per second
// The cycle repeats 8000/(16*4) ~= 122 times per seconds, enough to avoid flicker.
// Green LEDs are on for 1/16 of possible time.
// Red LEDs are on for 1/8 of possible time.
// ---------------------------------------------------------------------------------------------------------------------
#include "io_matrix__scanner__thread.h"
#include "leds_bar__data.h"

#include <stdint.h>
#include <cpu/avr/util/vthreads.h>
#include <cpu/avr/asm.h>

#include "cpu/avr/drivers/io_matrix/io_matrix__in.h"
#include "drivers/io_matrix/io_matrix__out_columns.h"
#include "drivers/io_matrix/io_matrix__out_rows.h"

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


#define io_matrix__scanner__thread__render_column(prev, curr, data, label)  \
    io_matrix__out__column##prev##__set(0);                                 \
    io_matrix__out__column##curr##__set(1);                                 \
    io_matrix__out_rows__set(data);                                         \
    VT_Z_YIELD_WITH_MARK_RETI(io_matrix__scanner__thread, io_matrix__scanner__thread__ip, label);


VT_FUNC(io_matrix__scanner__thread__function, io_matrix__scanner__thread__function_attrs) {
    FC_RESUME(io_matrix__scanner__thread__ip);
    {
        VT_MARK(io_matrix__scanner__thread, BEGIN);

        io_matrix__scanner__thread__render_column(3, 0, 0x0F, C0_0)
        io_matrix__scanner__thread__render_column(0, 1, 0x0F, C1_0)
        io_matrix__scanner__thread__render_column(1, 2, 0xF0, C2_0)
        io_matrix__scanner__thread__render_column(2, 3, 0xF0, C3_0)

        io_matrix__scanner__thread__render_column(3, 0, 0x0F, C0_1)
        io_matrix__scanner__thread__render_column(0, 1, 0x0F, C1_1)
        io_matrix__scanner__thread__render_column(1, 2, 0x00, C2_1)
        io_matrix__scanner__thread__render_column(2, 3, 0x00, C3_1)

        io_matrix__scanner__thread__render_column(3, 0, 0x0F, C0_2)
        io_matrix__scanner__thread__render_column(0, 1, 0x0F, C1_2)
        io_matrix__scanner__thread__render_column(1, 2, 0x00, C2_2)
        io_matrix__scanner__thread__render_column(2, 3, 0x00, C3_2)

        io_matrix__scanner__thread__render_column(3, 0, 0x0F, C0_3)
        io_matrix__scanner__thread__render_column(0, 1, 0x0F, C1_3)
        io_matrix__scanner__thread__render_column(1, 2, 0x00, C2_3)
        io_matrix__scanner__thread__render_column(2, 3, 0x00, C3_3)

        io_matrix__scanner__thread__render_column(3, 0, 0x0F, C0_4)
        io_matrix__scanner__thread__render_column(0, 1, 0x0F, C1_4)
        io_matrix__scanner__thread__render_column(1, 2, 0x00, C2_4)
        io_matrix__scanner__thread__render_column(2, 3, 0x00, C3_4)

        io_matrix__scanner__thread__render_column(3, 0, 0x0F, C0_5)
        io_matrix__scanner__thread__render_column(0, 1, 0x0F, C1_5)
        io_matrix__scanner__thread__render_column(1, 2, 0x00, C2_5)
        io_matrix__scanner__thread__render_column(2, 3, 0x00, C3_5)

        io_matrix__scanner__thread__render_column(3, 0, 0x0F, C0_6)
        io_matrix__scanner__thread__render_column(0, 1, 0x0F, C1_6)
        io_matrix__scanner__thread__render_column(1, 2, 0x00, C2_6)
        io_matrix__scanner__thread__render_column(2, 3, 0x00, C3_6)

        io_matrix__scanner__thread__render_column(3, 0, 0x0F, C0_7)
        io_matrix__scanner__thread__render_column(0, 1, 0x0F, C1_7)
        io_matrix__scanner__thread__render_column(1, 2, 0x00, C2_7)
        io_matrix__scanner__thread__render_column(2, 3, 0x00, C3_7)


        io_matrix__scanner__thread__render_column(3, 0, 0x00, C0_8)
        io_matrix__scanner__thread__render_column(0, 1, 0x00, C1_8)
        io_matrix__scanner__thread__render_column(1, 2, 0x00, C2_8)
        io_matrix__scanner__thread__render_column(2, 3, 0x00, C3_8)

        io_matrix__scanner__thread__render_column(3, 0, 0x00, C0_9)
        io_matrix__scanner__thread__render_column(0, 1, 0x00, C1_9)
        io_matrix__scanner__thread__render_column(1, 2, 0x00, C2_9)
        io_matrix__scanner__thread__render_column(2, 3, 0x00, C3_9)

        io_matrix__scanner__thread__render_column(3, 0, 0x00, C0_A)
        io_matrix__scanner__thread__render_column(0, 1, 0x00, C1_A)
        io_matrix__scanner__thread__render_column(1, 2, 0x00, C2_A)
        io_matrix__scanner__thread__render_column(2, 3, 0x00, C3_A)

        io_matrix__scanner__thread__render_column(3, 0, 0x00, C0_B)
        io_matrix__scanner__thread__render_column(0, 1, 0x00, C1_B)
        io_matrix__scanner__thread__render_column(1, 2, 0x00, C2_B)
        io_matrix__scanner__thread__render_column(2, 3, 0x00, C3_B)

        io_matrix__scanner__thread__render_column(3, 0, 0x00, C0_C)
        io_matrix__scanner__thread__render_column(0, 1, 0x00, C1_C)
        io_matrix__scanner__thread__render_column(1, 2, 0x00, C2_C)
        io_matrix__scanner__thread__render_column(2, 3, 0x00, C3_C)

        io_matrix__scanner__thread__render_column(3, 0, 0x00, C0_D)
        io_matrix__scanner__thread__render_column(0, 1, 0x00, C1_D)
        io_matrix__scanner__thread__render_column(1, 2, 0x00, C2_D)
        io_matrix__scanner__thread__render_column(2, 3, 0x00, C3_D)

        io_matrix__scanner__thread__render_column(3, 0, 0x00, C0_E)
        io_matrix__scanner__thread__render_column(0, 1, 0x00, C1_E)
        io_matrix__scanner__thread__render_column(1, 2, 0x00, C2_E)
        io_matrix__scanner__thread__render_column(2, 3, 0x00, C3_E)

        io_matrix__scanner__thread__render_column(3, 0, 0x00, C0_F)
        io_matrix__scanner__thread__render_column(0, 1, 0x00, C1_F)
        io_matrix__scanner__thread__render_column(1, 2, 0x00, C2_F)
        io_matrix__scanner__thread__render_column(2, 3, 0x00, C3_F)


        io_matrix__scanner__thread__render_column(3, 0, 0x00, C0_10)
        io_matrix__scanner__thread__render_column(0, 1, 0x00, C1_10)
        io_matrix__scanner__thread__render_column(1, 2, 0x00, C2_10)
        io_matrix__scanner__thread__render_column(2, 3, 0x00, C3_10)

        io_matrix__scanner__thread__render_column(3, 0, 0x00, C0_11)
        io_matrix__scanner__thread__render_column(0, 1, 0x00, C1_11)
        io_matrix__scanner__thread__render_column(1, 2, 0x00, C2_11)
        io_matrix__scanner__thread__render_column(2, 3, 0x00, C3_11)

        io_matrix__scanner__thread__render_column(3, 0, 0x00, C0_12)
        io_matrix__scanner__thread__render_column(0, 1, 0x00, C1_12)
        io_matrix__scanner__thread__render_column(1, 2, 0x00, C2_12)
        io_matrix__scanner__thread__render_column(2, 3, 0x00, C3_12)

        io_matrix__scanner__thread__render_column(3, 0, 0x00, C0_13)
        io_matrix__scanner__thread__render_column(0, 1, 0x00, C1_13)
        io_matrix__scanner__thread__render_column(1, 2, 0x00, C2_13)
        io_matrix__scanner__thread__render_column(2, 3, 0x00, C3_13)

        io_matrix__scanner__thread__render_column(3, 0, 0x00, C0_14)
        io_matrix__scanner__thread__render_column(0, 1, 0x00, C1_14)
        io_matrix__scanner__thread__render_column(1, 2, 0x00, C2_14)
        io_matrix__scanner__thread__render_column(2, 3, 0x00, C3_14)

        io_matrix__scanner__thread__render_column(3, 0, 0x00, C0_15)
        io_matrix__scanner__thread__render_column(0, 1, 0x00, C1_15)
        io_matrix__scanner__thread__render_column(1, 2, 0x00, C2_15)
        io_matrix__scanner__thread__render_column(2, 3, 0x00, C3_15)

        io_matrix__scanner__thread__render_column(3, 0, 0x00, C0_16)
        io_matrix__scanner__thread__render_column(0, 1, 0x00, C1_16)
        io_matrix__scanner__thread__render_column(1, 2, 0x00, C2_16)
        io_matrix__scanner__thread__render_column(2, 3, 0x00, C3_16)

        io_matrix__scanner__thread__render_column(3, 0, 0x00, C0_17)
        io_matrix__scanner__thread__render_column(0, 1, 0x00, C1_17)
        io_matrix__scanner__thread__render_column(1, 2, 0x00, C2_17)
        io_matrix__scanner__thread__render_column(2, 3, 0x00, C3_17)


        io_matrix__scanner__thread__render_column(3, 0, 0x00, C0_18)
        io_matrix__scanner__thread__render_column(0, 1, 0x00, C1_18)
        io_matrix__scanner__thread__render_column(1, 2, 0x00, C2_18)
        io_matrix__scanner__thread__render_column(2, 3, 0x00, C3_18)

        io_matrix__scanner__thread__render_column(3, 0, 0x00, C0_19)
        io_matrix__scanner__thread__render_column(0, 1, 0x00, C1_19)
        io_matrix__scanner__thread__render_column(1, 2, 0x00, C2_19)
        io_matrix__scanner__thread__render_column(2, 3, 0x00, C3_19)

        io_matrix__scanner__thread__render_column(3, 0, 0x00, C0_1A)
        io_matrix__scanner__thread__render_column(0, 1, 0x00, C1_1A)
        io_matrix__scanner__thread__render_column(1, 2, 0x00, C2_1A)
        io_matrix__scanner__thread__render_column(2, 3, 0x00, C3_1A)

        io_matrix__scanner__thread__render_column(3, 0, 0x00, C0_1B)
        io_matrix__scanner__thread__render_column(0, 1, 0x00, C1_1B)
        io_matrix__scanner__thread__render_column(1, 2, 0x00, C2_1B)
        io_matrix__scanner__thread__render_column(2, 3, 0x00, C3_1B)

        io_matrix__scanner__thread__render_column(3, 0, 0x00, C0_1C)
        io_matrix__scanner__thread__render_column(0, 1, 0x00, C1_1C)
        io_matrix__scanner__thread__render_column(1, 2, 0x00, C2_1C)
        io_matrix__scanner__thread__render_column(2, 3, 0x00, C3_1C)

        io_matrix__scanner__thread__render_column(3, 0, 0x00, C0_1D)
        io_matrix__scanner__thread__render_column(0, 1, 0x00, C1_1D)
        io_matrix__scanner__thread__render_column(1, 2, 0x00, C2_1D)
        io_matrix__scanner__thread__render_column(2, 3, 0x00, C3_1D)

        io_matrix__scanner__thread__render_column(3, 0, 0x00, C0_1E)
        io_matrix__scanner__thread__render_column(0, 1, 0x00, C1_1E)
        io_matrix__scanner__thread__render_column(1, 2, 0x00, C2_1E)
        io_matrix__scanner__thread__render_column(2, 3, 0x00, C3_1E)

        io_matrix__scanner__thread__render_column(3, 0, 0x00, C0_1F)
        io_matrix__scanner__thread__render_column(0, 1, 0x00, C1_1F)
        io_matrix__scanner__thread__render_column(1, 2, 0x00, C2_1F)
        io_matrix__scanner__thread__render_column(2, 3, 0x00, C3_1F)


        VT_Z_GOTO_RETI(io_matrix__scanner__thread, io_matrix__scanner__thread__ip, BEGIN);
    }
}
