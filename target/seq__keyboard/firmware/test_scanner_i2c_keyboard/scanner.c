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

#include "drivers/io_matrix__out_columns.h"
#include "drivers/io_matrix__out_rows.h"
#include "drivers/keyboard__pins.h"

#include "data.h"


// Logical keyboard ports
// ---------------------------------------------------------------------------------------------------------------------

#if defined(KEYBOARD__PORT_A__USED) && KEYBOARD__PORT_A__USED == 1

#ifdef KEYBOARD__PORT_A__STATE__REG
register volatile uint8_t keyboard__port_a__state asm(QUOTE(KEYBOARD__PORT_A__STATE__REG));
#else

volatile uint8_t keyboard__port_a__state;

void keyboard__pins__port_a__state__set(const uint8_t state) {
    keyboard__port_a__state = state;
}

#endif


uint8_t keyboard__pins__port_a__read(void) {
    return keyboard__port_a__state;
}

#endif


#if defined(KEYBOARD__PORT_B__USED) && KEYBOARD__PORT_B__USED == 1

#ifdef KEYBOARD__PORT_B__STATE__REG
register volatile uint8_t keyboard__port_b__state asm(QUOTE(KEYBOARD__PORT_B__STATE__REG));
#else
volatile uint8_t keyboard__port_b__state;
#endif


uint8_t keyboard__pins__port_b__read(void) {
    return keyboard__port_b__state;
}

#endif


#if defined(KEYBOARD__PORT_C__USED) && KEYBOARD__PORT_C__USED == 1

#ifdef KEYBOARD__PORT_C__STATE__REG
register volatile uint8_t keyboard__port_c__state asm(QUOTE(KEYBOARD__PORT_C__STATE__REG));
#else
volatile uint8_t keyboard__port_c__state;
#endif


uint8_t keyboard__pins__port_c__read(void) {
    return keyboard__port_c__state;
}

#endif


#if defined(KEYBOARD__PORT_D__USED) && KEYBOARD__PORT_D__USED == 1

#ifdef KEYBOARD__PORT_D__STATE__REG
register volatile uint8_t keyboard__port_d__state asm(QUOTE(KEYBOARD__PORT_D__STATE__REG));
#else
volatile uint8_t keyboard__port_d__state;
#endif


uint8_t keyboard__pins__port_d__read(void) {
    return keyboard__port_d__state;
}

#endif



void keyboard__pins__init(void) {
    keyboard__port_a__state = 0xFF;
    keyboard__port_b__state = 0xFF;
    keyboard__port_c__state = 0xFF;
    keyboard__port_d__state = 0xFF;
}


// Scanner thread
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
#ifdef KEYBOARD__PORT_A__STATE__REG
        __IN(keyboard__port_a__state, PIN_REG(SIGNAL_PORT(IN__BUTTONS)))
#else
        keyboard__port_a__state = IN(IN__BUTTONS);
#endif
        VT_Z_YIELD_WITH_MARK_RETI(scanner__thread, scanner__thread__ip, COLUMN1);


        io_matrix__out__column0__set(0);
        io_matrix__out__column1__set(1);
        io_matrix__out_rows__set(data__leds[1]);

        VT_Z_YIELD_WITH_MARK_RETI(scanner__thread, scanner__thread__ip, COLUMN1_READ);
#ifdef KEYBOARD__PORT_B__STATE__REG
        __IN(keyboard__port_b__state, PIN_REG(SIGNAL_PORT(IN__BUTTONS)))
#else
        keyboard__port_b__state = IN(IN__BUTTONS);
#endif
        VT_Z_YIELD_WITH_MARK_RETI(scanner__thread, scanner__thread__ip, COLUMN2);


        io_matrix__out__column1__set(0);
        io_matrix__out__column2__set(1);
        io_matrix__out_rows__set(data__leds[2]);

        VT_Z_YIELD_WITH_MARK_RETI(scanner__thread, scanner__thread__ip, COLUMN2_READ);
#ifdef KEYBOARD__PORT_C__STATE__REG
        __IN(keyboard__port_c__state, PIN_REG(SIGNAL_PORT(IN__BUTTONS)))
#else
        keyboard__port_c__state = IN(IN__BUTTONS);
#endif
        VT_Z_YIELD_WITH_MARK_RETI(scanner__thread, scanner__thread__ip, COLUMN3);


        io_matrix__out__column2__set(0);
        io_matrix__out__column3__set(1);
        io_matrix__out_rows__set(data__leds[3]);

        VT_Z_YIELD_WITH_MARK_RETI(scanner__thread, scanner__thread__ip, COLUMN3_READ);
#ifdef KEYBOARD__PORT_D__STATE__REG
        __IN(keyboard__port_d__state, PIN_REG(SIGNAL_PORT(IN__BUTTONS)))
#else
        keyboard__port_d__state = IN(IN__BUTTONS);
#endif
        VT_Z_GOTO_RETI(scanner__thread, scanner__thread__ip, BEGIN);
    }
}
