#include <cpu/avr/drivers/io_matrix/io_matrix__in.h>
#include <stdint.h>
#include "cpu/avr/asm.h"
#include "cpu/avr/gpio.h"


// Column states
// ---------------------------------------------------------------------------------------------------------------------


#ifdef IO_MATRIX__OUT__COLUMN0__PIN

#ifndef IO_MATRIX__IN__COLUMN0__STATE__REG
volatile uint8_t io_matrix__in__column0__state;
#endif

uint8_t io_matrix__in__column0__state__update(void) {
#ifdef IO_MATRIX__IN__COLUMN0__STATE__REG
    ZERO_REG(io_matrix__in__column0__state);
//    SET_BIT_IF_IO_BIT_IS_SET(io_matrix__in__column0__state, PIN_REG(SIGNAL_PORT(IO_MATRIX__IN__ROW0__PIN)), IO_MATRIX__IN__ROW0__PIN);
    // IO_MATRIX__IN__ROW0__PIN

#else

#endif
    return io_matrix__in__column0__state;
}

#endif



#ifdef IO_MATRIX__OUT__COLUMN1__PIN

#ifndef IO_MATRIX__IN__COLUMN1__STATE__REG
volatile uint8_t io_matrix__in__column1__state;
#endif

void io_matrix__in__column1__state__update(void) {
#ifdef IO_MATRIX__IN__COLUMN1__STATE__REG
#else
#endif
}

#endif



#ifdef IO_MATRIX__OUT__COLUMN2__PIN

#ifndef IO_MATRIX__IN__COLUMN2__STATE__REG
volatile uint8_t io_matrix__in__column2__state;
#endif

void io_matrix__in__column2__state__update(void) {
#ifdef IO_MATRIX__IN__COLUMN2__STATE__REG
#else
#endif
}

#endif



#ifdef IO_MATRIX__OUT__COLUMN3__PIN

#ifndef IO_MATRIX__IN__COLUMN3__STATE__REG
volatile uint8_t io_matrix__in__column3__state;
#endif

    void io_matrix__in__column3__state__update(void) {
#ifdef IO_MATRIX__IN__COLUMN3__STATE__REG
#else
#endif
    }

#endif


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
    }


    void io_matrix__in__start(void) {
        __asm__ __volatile__("io_matrix__in__start:");
#if defined(IO_MATRIX__IN__PORT) && defined(IO_MATRIX__IN__ROW0__PIN)
        io_matrix__in__column0__state = 0xFF;
#endif
#if defined(IO_MATRIX__IN__PORT) && defined(IO_MATRIX__IN__ROW1__PIN)
        io_matrix__in__column1__state = 0xFF;
#endif
#if defined(IO_MATRIX__IN__PORT) && defined(IO_MATRIX__IN__ROW2__PIN)
        io_matrix__in__column2__state = 0xFF;
#endif
#if defined(IO_MATRIX__IN__PORT) && defined(IO_MATRIX__IN__ROW3__PIN)
        io_matrix__in__column3__state = 0xFF;
#endif
}
