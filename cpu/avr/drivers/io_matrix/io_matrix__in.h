#ifndef __CPU__AVR__DRIVERS__IO_MATRIX__IO_MATRIX__IN_H
#define __CPU__AVR__DRIVERS__IO_MATRIX__IO_MATRIX__IN_H

#include <stdint.h>
#include "cpu/avr/gpio.h"
#include "cpu/avr/asm.h"


#ifdef IO_MATRIX__IN__COLUMN0__STATE__REG
register volatile uint8_t io_matrix__in__column0__state asm(QUOTE(IO_MATRIX__IN__COLUMN0__STATE__REG));
#else
extern volatile uint8_t io_matrix__in__column0__state;
#endif

#ifdef IO_MATRIX__IN__COLUMN1__STATE__REG
register volatile uint8_t io_matrix__in__column1__state asm(QUOTE(IO_MATRIX__IN__COLUMN1__STATE__REG));
#else
extern volatile uint8_t io_matrix__in__column1__state;
#endif

#ifdef IO_MATRIX__IN__COLUMN2__STATE__REG
register volatile uint8_t io_matrix__in__column2__state asm(QUOTE(IO_MATRIX__IN__COLUMN2__STATE__REG));
#else
extern volatile uint8_t io_matrix__in__column2__state;
#endif

#ifdef IO_MATRIX__IN__COLUMN3__STATE__REG
register volatile uint8_t io_matrix__in__column3__state asm(QUOTE(IO_MATRIX__IN__COLUMN3__STATE__REG));
#else
extern volatile uint8_t io_matrix__in__column3__state;
#endif


void io_matrix__in__column0__state__update(void);
uint8_t io_matrix__in__column0__state__get(void) {
    FIX_REGISTER(io_matrix__in__column0__state);
    return io_matrix__in__column0__state;
}

void io_matrix__in__column1__state__update(void);
uint8_t io_matrix__in__column1__state__get(void) {
    FIX_REGISTER(io_matrix__in__column1__state);
    return io_matrix__in__column1__state;
}

void io_matrix__in__column2__state__update(void);
uint8_t io_matrix__in__column2__state__get(void) {
    FIX_REGISTER(io_matrix__in__column2__state);
    return io_matrix__in__column2__state;
}

void io_matrix__in__column3__state__update(void);
uint8_t io_matrix__in__column3__state__get(void) {
    FIX_REGISTER(io_matrix__in__column3__state);
    return io_matrix__in__column3__state;
}


void io_matrix__in__init(void);

void io_matrix__in__start(void);


#endif