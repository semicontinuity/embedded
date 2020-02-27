#include <cpu/avr/drivers/io_matrix/io_matrix__in.h>
#include <stdint.h>
#include "cpu/avr/asm.h"
#include "cpu/avr/gpio.h"


// Column states
// ---------------------------------------------------------------------------------------------------------------------

#ifndef IO_MATRIX__IN__COLUMN0__STATE__REG
volatile uint8_t io_matrix__in__column0__state;
#endif

uint8_t io_matrix__in__column0__state__update(void) {
#ifdef IO_MATRIX__IN__COLUMN0__STATE__REG
    __IN(io_matrix__in__column0__state, PIN_REG(SIGNAL_PORT(IO_MATRIX__IN)))
#else
    io_matrix__in__column0__state = IN(IO_MATRIX__IN);
#endif
    return io_matrix__in__column0__state;
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


void io_matrix__in__init(void) {
    __asm__ __volatile__("io_matrix__in__init:");
#if defined(IO_MATRIX__IN__PORT) && defined(IO_MATRIX__IN__ROW0__PIN)
    USE_PIN_AS_INPUT(IO_MATRIX__IN__PORT, IO_MATRIX__IN__ROW0__PIN);
    ENABLE_PIN_PULLUP(IO_MATRIX__IN__PORT, IO_MATRIX__IN__ROW0__PIN);
#endif
#if defined(IO_MATRIX__IN__PORT) && defined(IO_MATRIX__IN__ROW1__PIN)
    USE_PIN_AS_INPUT(IO_MATRIX__IN__PORT, IO_MATRIX__IN__ROW1__PIN);
    ENABLE_PIN_PULLUP(IO_MATRIX__IN__PORT, IO_MATRIX__IN__ROW1__PIN);
#endif
#if defined(IO_MATRIX__IN__PORT) && defined(IO_MATRIX__IN__ROW2__PIN)
    USE_PIN_AS_INPUT(IO_MATRIX__IN__PORT, IO_MATRIX__IN__ROW2__PIN);
    ENABLE_PIN_PULLUP(IO_MATRIX__IN__PORT, IO_MATRIX__IN__ROW2__PIN);
#endif
#if defined(IO_MATRIX__IN__PORT) && defined(IO_MATRIX__IN__ROW3__PIN)
    USE_PIN_AS_INPUT(IO_MATRIX__IN__PORT, IO_MATRIX__IN__ROW3__PIN);
    ENABLE_PIN_PULLUP(IO_MATRIX__IN__PORT, IO_MATRIX__IN__ROW3__PIN);
#endif
#if defined(IO_MATRIX__IN__PORT) && defined(IO_MATRIX__IN__ROW4__PIN)
    USE_PIN_AS_INPUT(IO_MATRIX__IN__PORT, IO_MATRIX__IN__ROW4__PIN);
    ENABLE_PIN_PULLUP(IO_MATRIX__IN__PORT, IO_MATRIX__IN__ROW4__PIN);
#endif
#if defined(IO_MATRIX__IN__PORT) && defined(IO_MATRIX__IN__ROW5__PIN)
    USE_PIN_AS_INPUT(IO_MATRIX__IN__PORT, IO_MATRIX__IN__ROW5__PIN);
    ENABLE_PIN_PULLUP(IO_MATRIX__IN__PORT, IO_MATRIX__IN__ROW5__PIN);
#endif
#if defined(IO_MATRIX__IN__PORT) && defined(IO_MATRIX__IN__ROW6__PIN)
    USE_PIN_AS_INPUT(IO_MATRIX__IN__PORT, IO_MATRIX__IN__ROW6__PIN);
    ENABLE_PIN_PULLUP(IO_MATRIX__IN__PORT, IO_MATRIX__IN__ROW6__PIN);
#endif
#if defined(IO_MATRIX__IN__PORT) && defined(IO_MATRIX__IN__ROW7__PIN)
    USE_PIN_AS_INPUT(IO_MATRIX__IN__PORT, IO_MATRIX__IN__ROW7__PIN);
    ENABLE_PIN_PULLUP(IO_MATRIX__IN__PORT, IO_MATRIX__IN__ROW7__PIN);
#endif
}


void io_matrix__in__start(void) {
    __asm__ __volatile__("io_matrix__in__start:");
    io_matrix__in__column0__state = 0xFF;
    io_matrix__in__column1__state = 0xFF;
    io_matrix__in__column2__state = 0xFF;
    io_matrix__in__column3__state = 0xFF;
}
