#ifndef __CPU__AVR__DRIVERS__IO_MATRIX__IO_MATRIX__IN_H
#define __CPU__AVR__DRIVERS__IO_MATRIX__IO_MATRIX__IN_H

#include <stdint.h>
#include "cpu/avr/gpio.h"
#include "cpu/avr/asm.h"



#ifdef IO_MATRIX__OUT__COLUMN0__PIN

#ifdef IO_MATRIX__IN__COLUMN0__STATE__REG
register volatile uint8_t io_matrix__in__column0__state asm(QUOTE(IO_MATRIX__IN__COLUMN0__STATE__REG));
#else
extern volatile uint8_t io_matrix__in__column0__state;
#endif

uint8_t io_matrix__in__column0__state__update(void);
uint8_t inline __attribute__((always_inline)) io_matrix__in__column0__state__get(void)  {
    // without FIX_REGISTER register somehow gets optimized away
    FIX_REGISTER(io_matrix__in__column0__state);
    return io_matrix__in__column0__state;
}

#endif



#ifdef IO_MATRIX__OUT__COLUMN1__PIN

#ifdef IO_MATRIX__IN__COLUMN1__STATE__REG
register volatile uint8_t io_matrix__in__column1__state asm(QUOTE(IO_MATRIX__IN__COLUMN1__STATE__REG));
#else
extern volatile uint8_t io_matrix__in__column1__state;
#endif

void io_matrix__in__column1__state__update(void);
uint8_t io_matrix__in__column1__state__get(void) {
    // without FIX_REGISTER register somehow gets optimized away
    FIX_REGISTER(io_matrix__in__column1__state);
    return io_matrix__in__column1__state;
}

#endif



#ifdef IO_MATRIX__OUT__COLUMN2__PIN

#ifdef IO_MATRIX__IN__COLUMN2__STATE__REG
register volatile uint8_t io_matrix__in__column2__state asm(QUOTE(IO_MATRIX__IN__COLUMN2__STATE__REG));
#else
extern volatile uint8_t io_matrix__in__column2__state;
#endif

void io_matrix__in__column2__state__update(void);
uint8_t io_matrix__in__column2__state__get(void) {
    // without FIX_REGISTER register somehow gets optimized away
    FIX_REGISTER(io_matrix__in__column2__state);
    return io_matrix__in__column2__state;
}

#endif



#ifdef IO_MATRIX__OUT__COLUMN3__PIN

#ifdef IO_MATRIX__IN__COLUMN3__STATE__REG
register volatile uint8_t io_matrix__in__column3__state asm(QUOTE(IO_MATRIX__IN__COLUMN3__STATE__REG));
#else
extern volatile uint8_t io_matrix__in__column3__state;
#endif

void io_matrix__in__column3__state__update(void);
uint8_t io_matrix__in__column3__state__get(void) {
    // without FIX_REGISTER register somehow gets optimized away
    FIX_REGISTER(io_matrix__in__column3__state);
    return io_matrix__in__column3__state;
}

#endif



#ifdef IO_MATRIX__OUT__COLUMN4__PIN

#ifdef IO_MATRIX__IN__COLUMN4__STATE__REG
register volatile uint8_t io_matrix__in__column4__state asm(QUOTE(IO_MATRIX__IN__COLUMN4__STATE__REG));
#else
extern volatile uint8_t io_matrix__in__column4__state;
#endif

void io_matrix__in__column4__state__update(void);
uint8_t io_matrix__in__column4__state__get(void) {
    // without FIX_REGISTER register somehow gets optimized away
    FIX_REGISTER(io_matrix__in__column4__state);
    return io_matrix__in__column4__state;
}

#endif



#ifdef IO_MATRIX__OUT__COLUMN5__PIN

#ifdef IO_MATRIX__IN__COLUMN5__STATE__REG
register volatile uint8_t io_matrix__in__column5__state asm(QUOTE(IO_MATRIX__IN__COLUMN5__STATE__REG));
#else
extern volatile uint8_t io_matrix__in__column5__state;
#endif

void io_matrix__in__column5__state__update(void);
uint8_t io_matrix__in__column5__state__get(void) {
    // without FIX_REGISTER register somehow gets optimized away
    FIX_REGISTER(io_matrix__in__column5__state);
    return io_matrix__in__column5__state;
}

#endif



#ifdef IO_MATRIX__OUT__COLUMN6__PIN

#ifdef IO_MATRIX__IN__COLUMN6__STATE__REG
register volatile uint8_t io_matrix__in__column6__state asm(QUOTE(IO_MATRIX__IN__COLUMN6__STATE__REG));
#else
extern volatile uint8_t io_matrix__in__column6__state;
#endif

void io_matrix__in__column6__state__update(void);
uint8_t io_matrix__in__column6__state__get(void) {
    // without FIX_REGISTER register somehow gets optimized away
    FIX_REGISTER(io_matrix__in__column6__state);
    return io_matrix__in__column6__state;
}

#endif



#ifdef IO_MATRIX__OUT__COLUMN7__PIN

#ifdef IO_MATRIX__IN__COLUMN7__STATE__REG
register volatile uint8_t io_matrix__in__column7__state asm(QUOTE(IO_MATRIX__IN__COLUMN7__STATE__REG));
#else
extern volatile uint8_t io_matrix__in__column7__state;
#endif

void io_matrix__in__column7__state__update(void);
uint8_t io_matrix__in__column7__state__get(void) {
    // without FIX_REGISTER register somehow gets optimized away
    FIX_REGISTER(io_matrix__in__column7__state);
    return io_matrix__in__column7__state;
}

#endif


void io_matrix__in__init(void);

void io_matrix__in__start(void);


#endif