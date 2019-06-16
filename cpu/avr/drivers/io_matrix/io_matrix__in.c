#include <cpu/avr/drivers/io_matrix/io_matrix__in.h>
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



inline void io_matrix__in__start(void) {
    io_matrix__in__column0__state = 0xFF;
    io_matrix__in__column1__state = 0xFF;
    io_matrix__in__column2__state = 0xFF;
    io_matrix__in__column3__state = 0xFF;
}
