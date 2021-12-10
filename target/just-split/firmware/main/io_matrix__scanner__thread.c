// I/O matrix scanner: handles reading of buttons in the I/O matrix, as well as rendering pattern on dual-color LEDs.
//
// Column is selected by issuing logical 1; pressed rows are those that read 0 (pull-ups enabled on row pins)
//
// This thread is executed very often.
// For this reason is optimized to use only the minimal number of hand-picked registers,
// that are not used in other threads.
// This way, it is possible to have very lightweight context switching (without lots of push-pop operations)
//
// In total, there are 128 time slots, 32 for each column.
// GREEN LED, if logically ON, is physically ON for 1 of 32 time slots.
// RED LED, if logically ON, is physically ON for 8 of 32 time slots.
// This is done to achieve appropriate LED brightness with chosen LEDs and resistors (300 Ohm)
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

//#define io_matrix__scanner__thread__render_column(prev, curr, data, label)  \
//io_matrix__out__column##prev##__set(0);                                     \
//{ register uint8_t __temp asm("r0");\
//  __LDS(__temp, data);                                                      \
//io_matrix__out_rows__set(__temp);                          \
//}                                                                           \
//io_matrix__out__column##curr##__set(1);                                     \
//VT_Z_YIELD_WITH_MARK_RETI(io_matrix__scanner__thread, io_matrix__scanner__thread__ip, label);


//#define io_matrix__scanner__thread__render_column(prev, curr, data, label)  \
//io_matrix__in__column##prev##__state__update();                             \
//io_matrix__out__column##prev##__set(0);                                     \
//io_matrix__out_rows__set(data);                                             \
//io_matrix__out__column##curr##__set(1);                                     \
//VT_Z_YIELD_WITH_MARK_RETI(io_matrix__scanner__thread, io_matrix__scanner__thread__ip, label);

//#define io_matrix__scanner__thread__render_column(prev, curr, data, label)  \
//io_matrix__out__column##prev##__set(0);                                     \
//io_matrix__out_rows__set(data);                                             \
//io_matrix__out__column##curr##__set(1);                                     \
//VT_Z_YIELD_WITH_MARK_RETI(io_matrix__scanner__thread, io_matrix__scanner__thread__ip, label);

#define io_matrix__scanner__thread__render_column(prev, curr, data, label)  \
io_matrix__in__column##prev##__state__update();                             \
io_matrix__out__column##prev##__set(0);                                     \
io_matrix__out__column##curr##__set(1);                                     \
VT_Z_YIELD_WITH_MARK_RETI(io_matrix__scanner__thread, io_matrix__scanner__thread__ip, label);


uint8_t io_matrix__scanner__thread__ld(uint8_t offset) {
    // Load LED array data via temp register (r0), which is only used in this thread
    // (this thread does not save registers - need to use non-intersecting sets of registers)
    register uint8_t __temp asm("r0");
    __LDS(__temp, leds_bar__data[offset]);
    return __temp;
}


VT_FUNC(io_matrix__scanner__thread__function, io_matrix__scanner__thread__function_attrs) {
    FC_RESUME(io_matrix__scanner__thread__ip);
    {
        VT_MARK(io_matrix__scanner__thread, BEGIN);


        io_matrix__scanner__thread__render_column(3, 0, io_matrix__scanner__thread__ld(0), C0_00)
        io_matrix__scanner__thread__render_column(0, 1, io_matrix__scanner__thread__ld(1), C1_00)
        io_matrix__scanner__thread__render_column(1, 2, io_matrix__scanner__thread__ld(2), C2_00)
        io_matrix__scanner__thread__render_column(2, 3, io_matrix__scanner__thread__ld(3), C3_00)

        io_matrix__scanner__thread__render_column(3, 0, io_matrix__scanner__thread__ld(0), C0_01)
        io_matrix__scanner__thread__render_column(0, 1, io_matrix__scanner__thread__ld(1), C1_01)
        io_matrix__scanner__thread__render_column(1, 2, 0x00, C2_01)
        io_matrix__scanner__thread__render_column(2, 3, 0x00, C3_01)

        io_matrix__scanner__thread__render_column(3, 0, io_matrix__scanner__thread__ld(0), C0_02)
        io_matrix__scanner__thread__render_column(0, 1, io_matrix__scanner__thread__ld(1), C1_02)
        io_matrix__scanner__thread__render_column(1, 2, 0x00, C2_02)
        io_matrix__scanner__thread__render_column(2, 3, 0x00, C3_02)

        io_matrix__scanner__thread__render_column(3, 0, io_matrix__scanner__thread__ld(0), C0_03)
        io_matrix__scanner__thread__render_column(0, 1, io_matrix__scanner__thread__ld(1), C1_03)
        io_matrix__scanner__thread__render_column(1, 2, 0x00, C2_03)
        io_matrix__scanner__thread__render_column(2, 3, 0x00, C3_03)

        io_matrix__scanner__thread__render_column(3, 0, io_matrix__scanner__thread__ld(0), C0_04)
        io_matrix__scanner__thread__render_column(0, 1, io_matrix__scanner__thread__ld(1), C1_04)
        io_matrix__scanner__thread__render_column(1, 2, 0x00, C2_04)
        io_matrix__scanner__thread__render_column(2, 3, 0x00, C3_04)

        io_matrix__scanner__thread__render_column(3, 0, io_matrix__scanner__thread__ld(0), C0_05)
        io_matrix__scanner__thread__render_column(0, 1, io_matrix__scanner__thread__ld(1), C1_05)
        io_matrix__scanner__thread__render_column(1, 2, 0x00, C2_05)
        io_matrix__scanner__thread__render_column(2, 3, 0x00, C3_05)

        io_matrix__scanner__thread__render_column(3, 0, io_matrix__scanner__thread__ld(0), C0_06)
        io_matrix__scanner__thread__render_column(0, 1, io_matrix__scanner__thread__ld(1), C1_06)
        io_matrix__scanner__thread__render_column(1, 2, 0x00, C2_06)
        io_matrix__scanner__thread__render_column(2, 3, 0x00, C3_06)

        io_matrix__scanner__thread__render_column(3, 0, io_matrix__scanner__thread__ld(0), C0_07)
        io_matrix__scanner__thread__render_column(0, 1, io_matrix__scanner__thread__ld(1), C1_07)
        io_matrix__scanner__thread__render_column(1, 2, 0x00, C2_07)
        io_matrix__scanner__thread__render_column(2, 3, 0x00, C3_07)


        io_matrix__scanner__thread__render_column(3, 0, 0x00, C0_08)
        io_matrix__scanner__thread__render_column(0, 1, 0x00, C1_08)
        io_matrix__scanner__thread__render_column(1, 2, 0x00, C2_08)
        io_matrix__scanner__thread__render_column(2, 3, 0x00, C3_08)

        io_matrix__scanner__thread__render_column(3, 0, 0x00, C0_09)
        io_matrix__scanner__thread__render_column(0, 1, 0x00, C1_09)
        io_matrix__scanner__thread__render_column(1, 2, 0x00, C2_09)
        io_matrix__scanner__thread__render_column(2, 3, 0x00, C3_09)

        io_matrix__scanner__thread__render_column(3, 0, 0x00, C0_0A)
        io_matrix__scanner__thread__render_column(0, 1, 0x00, C1_0A)
        io_matrix__scanner__thread__render_column(1, 2, 0x00, C2_0A)
        io_matrix__scanner__thread__render_column(2, 3, 0x00, C3_0A)

        io_matrix__scanner__thread__render_column(3, 0, 0x00, C0_0B)
        io_matrix__scanner__thread__render_column(0, 1, 0x00, C1_0B)
        io_matrix__scanner__thread__render_column(1, 2, 0x00, C2_0B)
        io_matrix__scanner__thread__render_column(2, 3, 0x00, C3_0B)

        io_matrix__scanner__thread__render_column(3, 0, 0x00, C0_0C)
        io_matrix__scanner__thread__render_column(0, 1, 0x00, C1_0C)
        io_matrix__scanner__thread__render_column(1, 2, 0x00, C2_0C)
        io_matrix__scanner__thread__render_column(2, 3, 0x00, C3_0C)

        io_matrix__scanner__thread__render_column(3, 0, 0x00, C0_0D)
        io_matrix__scanner__thread__render_column(0, 1, 0x00, C1_0D)
        io_matrix__scanner__thread__render_column(1, 2, 0x00, C2_0D)
        io_matrix__scanner__thread__render_column(2, 3, 0x00, C3_0D)

        io_matrix__scanner__thread__render_column(3, 0, 0x00, C0_0E)
        io_matrix__scanner__thread__render_column(0, 1, 0x00, C1_0E)
        io_matrix__scanner__thread__render_column(1, 2, 0x00, C2_0E)
        io_matrix__scanner__thread__render_column(2, 3, 0x00, C3_0E)

        io_matrix__scanner__thread__render_column(3, 0, 0x00, C0_0F)
        io_matrix__scanner__thread__render_column(0, 1, 0x00, C1_0F)
        io_matrix__scanner__thread__render_column(1, 2, 0x00, C2_0F)
        io_matrix__scanner__thread__render_column(2, 3, 0x00, C3_0F)


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
