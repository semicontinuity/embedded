// Scanner: handles rendering of LED colors and reading of buttons in the I/O matrix
// ---------------------------------------------------------------------------------------------------------------------

#include <stdint.h>
#include <cpu/avr/util/vthreads.h>
#include <drivers/out/columns.h>
#include "scanner.h"
#include "data.h"


// Logical keyboard ports
// ---------------------------------------------------------------------------------------------------------------------

#if defined(KEYBOARD__PORT_A__USED) && KEYBOARD__PORT_A__USED == 1

#ifdef KEYBOARD__PORT_A__STATE__REG
register volatile uint8_t keyboard__port_a__state asm(QUOTE(KEYBOARD__PORT_A__STATE__REG));
#else
volatile uint8_t keyboard__port_a__state;
#endif

void keyboard__pins__port_a__state__set(const uint8_t state) {
    keyboard__port_a__state = state;
}

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

void keyboard__pins__port_b__state__set(const uint8_t state) {
    keyboard__port_b__state = state;
}

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

void keyboard__pins__port_c__state__set(const uint8_t state) {
    keyboard__port_c__state = state;
}

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

void keyboard__pins__port_d__state__set(const uint8_t state) {
    keyboard__port_d__state = state;
}

uint8_t keyboard__pins__port_d__read(void) {
    return keyboard__port_d__state;
}

#endif



void keyboard__pins__init(void) {
    keyboard__pins__port_a__state__set(0xFF);
    keyboard__pins__port_b__state__set(0xFF);
    keyboard__pins__port_c__state__set(0xFF);
    keyboard__pins__port_d__state__set(0xFF);
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
