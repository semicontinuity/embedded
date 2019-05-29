#include "drivers/io_matrix__in.h"
#include <stdint.h>
#include "cpu/avr/asm.h"
#include "cpu/avr/gpio.h"


// Column states
// ---------------------------------------------------------------------------------------------------------------------

#ifndef IO_MATRIX__IN__COLUMN0__STATE__REG
volatile uint8_t io_matrix__in__column0__state;
#endif

void io_matrix__in__column0__state__update(void) {
#ifdef IO_MATRIX__IN__COLUMN0__STATE__REG
    __IN(io_matrix__in__column0__state, PIN_REG(SIGNAL_PORT(IO_MATRIX__IN)))
#else
    io_matrix__in__column0__state = IN(IO_MATRIX__IN);
#endif
}



#ifndef IO_MATRIX__IN__COLUMN1__STATE__REG
volatile uint8_t io_matrix__in__column1__state;
#endif

void io_matrix__in__column1__state__update(void) {
#ifdef IO_MATRIX__IN__COLUMN1__STATE__REG
    __IN(io_matrix__in__column1__state, PIN_REG(SIGNAL_PORT(IO_MATRIX__IN)))
#else
    io_matrix__in__column1__state = IN(IO_MATRIX__IN);
#endif
}



#ifndef IO_MATRIX__IN__COLUMN2__STATE__REG
volatile uint8_t io_matrix__in__column2__state;
#endif

void io_matrix__in__column2__state__update(void) {
#ifdef IO_MATRIX__IN__COLUMN2__STATE__REG
    __IN(io_matrix__in__column2__state, PIN_REG(SIGNAL_PORT(IO_MATRIX__IN)))
#else
    io_matrix__in__column2__state = IN(IO_MATRIX__IN);
#endif
}



#ifndef IO_MATRIX__IN__COLUMN3__STATE__REG
volatile uint8_t io_matrix__in__column3__state;
#endif

void io_matrix__in__column3__state__update(void) {
#ifdef IO_MATRIX__IN__COLUMN3__STATE__REG
    __IN(io_matrix__in__column3__state, PIN_REG(SIGNAL_PORT(IO_MATRIX__IN)))
#else
    io_matrix__in__column3__state = IN(IO_MATRIX__IN);
#endif
}



inline void io_matrix__in__init(void) {
#if defined(IO_MATRIX__IN__ROW0__PORT) && defined(IO_MATRIX__IN__ROW0__PIN)
    USE_AS_OUTPUT(IO_MATRIX__IN__ROW0);
#endif
#if defined(IO_MATRIX__IN__ROW1__PORT) && defined(IO_MATRIX__IN__ROW1__PIN)
    USE_AS_OUTPUT(IO_MATRIX__IN__ROW1);
#endif
#if defined(IO_MATRIX__IN__ROW2__PORT) && defined(IO_MATRIX__IN__ROW2__PIN)
    USE_AS_OUTPUT(IO_MATRIX__IN__ROW2);
#endif
#if defined(IO_MATRIX__IN__ROW3__PORT) && defined(IO_MATRIX__IN__ROW3__PIN)
    USE_AS_OUTPUT(IO_MATRIX__IN__ROW3);
#endif
#if defined(IO_MATRIX__IN__ROW4__PORT) && defined(IO_MATRIX__IN__ROW4__PIN)
    USE_AS_OUTPUT(IO_MATRIX__IN__ROW4);
#endif
#if defined(IO_MATRIX__IN__ROW5__PORT) && defined(IO_MATRIX__IN__ROW5__PIN)
    USE_AS_OUTPUT(IO_MATRIX__IN__ROW5);
#endif
#if defined(IO_MATRIX__IN__ROW6__PORT) && defined(IO_MATRIX__IN__ROW6__PIN)
    USE_AS_OUTPUT(IO_MATRIX__IN__ROW6);
#endif
#if defined(IO_MATRIX__IN__ROW7__PORT) && defined(IO_MATRIX__IN__ROW7__PIN)
    USE_AS_OUTPUT(IO_MATRIX__IN__ROW7);
#endif

    io_matrix__in__column0__state = 0xFF;
    io_matrix__in__column1__state = 0xFF;
    io_matrix__in__column2__state = 0xFF;
    io_matrix__in__column3__state = 0xFF;
}
