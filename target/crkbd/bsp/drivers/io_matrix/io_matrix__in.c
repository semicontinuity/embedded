// Hard-coded to use rows at ports C and B
// Clobbers T bit - T bit must not be used elsewhere

#include <cpu/avr/drivers/io_matrix/io_matrix__in.h>
#include <stdint.h>
#include "cpu/avr/asm.h"
#include "cpu/avr/gpio.h"


#ifdef IO_MATRIX__IN__TEMP__REG
register volatile uint8_t io_matrix__in__temp asm(QUOTE(IO_MATRIX__IN__TEMP__REG));

#endif


// Column states
// ---------------------------------------------------------------------------------------------------------------------


#ifdef IO_MATRIX__OUT__COLUMN0__PIN

#ifndef IO_MATRIX__IN__COLUMN0__STATE__REG
volatile uint8_t io_matrix__in__column0__state;
#endif

uint8_t io_matrix__in__column0__state__update(void) {
#ifdef IO_MATRIX__IN__COLUMN0__STATE__REG
    __IN(io_matrix__in__column0__state, PIN_REG(SIGNAL_PORT(IO_MATRIX__IN)));

# ifdef IO_MATRIX__IN__ALT__PORT
    __IN(io_matrix__in__temp, PIN_REG(SIGNAL_PORT(IO_MATRIX__IN__ALT)));

#  ifdef IO_MATRIX__IN__ROW0__BIT
    COPY_BIT(io_matrix__in__temp, IO_MATRIX__IN__ROW0__PIN, io_matrix__in__column0__state, IO_MATRIX__IN__ROW0__BIT);
#  endif

#  ifdef IO_MATRIX__IN__ROW1__BIT
    COPY_BIT(io_matrix__in__temp, IO_MATRIX__IN__ROW1__PIN, io_matrix__in__column0__state, IO_MATRIX__IN__ROW1__BIT);
#  endif

#  ifdef IO_MATRIX__IN__ROW2__BIT
    COPY_BIT(io_matrix__in__temp, IO_MATRIX__IN__ROW2__PIN, io_matrix__in__column0__state, IO_MATRIX__IN__ROW2__BIT);
#  endif

#  ifdef IO_MATRIX__IN__ROW3__BIT
    COPY_BIT(io_matrix__in__temp, IO_MATRIX__IN__ROW3__PIN, io_matrix__in__column0__state, IO_MATRIX__IN__ROW3__BIT);
#  endif

#  ifdef IO_MATRIX__IN__ROW4__BIT
    COPY_BIT(io_matrix__in__temp, IO_MATRIX__IN__ROW4__PIN, io_matrix__in__column0__state, IO_MATRIX__IN__ROW4__BIT);
#  endif

#  ifdef IO_MATRIX__IN__ROW5__BIT
    COPY_BIT(io_matrix__in__temp, IO_MATRIX__IN__ROW5__PIN, io_matrix__in__column0__state, IO_MATRIX__IN__ROW5__BIT);
#  endif

#  ifdef IO_MATRIX__IN__ROW6__BIT
    COPY_BIT(io_matrix__in__temp, IO_MATRIX__IN__ROW6__PIN, io_matrix__in__column0__state, IO_MATRIX__IN__ROW6__BIT);
#  endif

#  ifdef IO_MATRIX__IN__ROW7__BIT
    COPY_BIT(io_matrix__in__temp, IO_MATRIX__IN__ROW7__PIN, io_matrix__in__column0__state, IO_MATRIX__IN__ROW7__BIT);
#  endif

# endif

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
    __IN(io_matrix__in__column1__state, PIN_REG(SIGNAL_PORT(IO_MATRIX__IN)));

# ifdef IO_MATRIX__IN__ALT__PORT
    __IN(io_matrix__in__temp, PIN_REG(SIGNAL_PORT(IO_MATRIX__IN__ALT)));

#  ifdef IO_MATRIX__IN__ROW0__BIT
    COPY_BIT(io_matrix__in__temp, IO_MATRIX__IN__ROW0__PIN, io_matrix__in__column1__state, IO_MATRIX__IN__ROW0__BIT);
#  endif

#  ifdef IO_MATRIX__IN__ROW1__BIT
    COPY_BIT(io_matrix__in__temp, IO_MATRIX__IN__ROW1__PIN, io_matrix__in__column1__state, IO_MATRIX__IN__ROW1__BIT);
#  endif

#  ifdef IO_MATRIX__IN__ROW2__BIT
    COPY_BIT(io_matrix__in__temp, IO_MATRIX__IN__ROW2__PIN, io_matrix__in__column1__state, IO_MATRIX__IN__ROW2__BIT);
#  endif

#  ifdef IO_MATRIX__IN__ROW3__BIT
    COPY_BIT(io_matrix__in__temp, IO_MATRIX__IN__ROW3__PIN, io_matrix__in__column1__state, IO_MATRIX__IN__ROW3__BIT);
#  endif

#  ifdef IO_MATRIX__IN__ROW4__BIT
    COPY_BIT(io_matrix__in__temp, IO_MATRIX__IN__ROW4__PIN, io_matrix__in__column1__state, IO_MATRIX__IN__ROW4__BIT);
#  endif

#  ifdef IO_MATRIX__IN__ROW5__BIT
    COPY_BIT(io_matrix__in__temp, IO_MATRIX__IN__ROW5__PIN, io_matrix__in__column1__state, IO_MATRIX__IN__ROW5__BIT);
#  endif

#  ifdef IO_MATRIX__IN__ROW6__BIT
    COPY_BIT(io_matrix__in__temp, IO_MATRIX__IN__ROW6__PIN, io_matrix__in__column1__state, IO_MATRIX__IN__ROW6__BIT);
#  endif

#  ifdef IO_MATRIX__IN__ROW7__BIT
    COPY_BIT(io_matrix__in__temp, IO_MATRIX__IN__ROW7__PIN, io_matrix__in__column1__state, IO_MATRIX__IN__ROW7__BIT);
#  endif

# endif

#endif
}

#endif



#ifdef IO_MATRIX__OUT__COLUMN2__PIN

#ifndef IO_MATRIX__IN__COLUMN2__STATE__REG
volatile uint8_t io_matrix__in__column2__state;
#endif

void io_matrix__in__column2__state__update(void) {
#ifdef IO_MATRIX__IN__COLUMN2__STATE__REG
    __IN(io_matrix__in__column2__state, PIN_REG(SIGNAL_PORT(IO_MATRIX__IN)));

# ifdef IO_MATRIX__IN__ALT__PORT
    __IN(io_matrix__in__temp, PIN_REG(SIGNAL_PORT(IO_MATRIX__IN__ALT)));

#  ifdef IO_MATRIX__IN__ROW0__BIT
    COPY_BIT(io_matrix__in__temp, IO_MATRIX__IN__ROW0__PIN, io_matrix__in__column2__state, IO_MATRIX__IN__ROW0__BIT);
#  endif

#  ifdef IO_MATRIX__IN__ROW1__BIT
    COPY_BIT(io_matrix__in__temp, IO_MATRIX__IN__ROW1__PIN, io_matrix__in__column2__state, IO_MATRIX__IN__ROW1__BIT);
#  endif

#  ifdef IO_MATRIX__IN__ROW2__BIT
    COPY_BIT(io_matrix__in__temp, IO_MATRIX__IN__ROW2__PIN, io_matrix__in__column2__state, IO_MATRIX__IN__ROW2__BIT);
#  endif

#  ifdef IO_MATRIX__IN__ROW3__BIT
    COPY_BIT(io_matrix__in__temp, IO_MATRIX__IN__ROW3__PIN, io_matrix__in__column2__state, IO_MATRIX__IN__ROW3__BIT);
#  endif

#  ifdef IO_MATRIX__IN__ROW4__BIT
    COPY_BIT(io_matrix__in__temp, IO_MATRIX__IN__ROW4__PIN, io_matrix__in__column2__state, IO_MATRIX__IN__ROW4__BIT);
#  endif

#  ifdef IO_MATRIX__IN__ROW5__BIT
    COPY_BIT(io_matrix__in__temp, IO_MATRIX__IN__ROW5__PIN, io_matrix__in__column2__state, IO_MATRIX__IN__ROW5__BIT);
#  endif

#  ifdef IO_MATRIX__IN__ROW6__BIT
    COPY_BIT(io_matrix__in__temp, IO_MATRIX__IN__ROW6__PIN, io_matrix__in__column2__state, IO_MATRIX__IN__ROW6__BIT);
#  endif

#  ifdef IO_MATRIX__IN__ROW7__BIT
    COPY_BIT(io_matrix__in__temp, IO_MATRIX__IN__ROW7__PIN, io_matrix__in__column2__state, IO_MATRIX__IN__ROW7__BIT);
#  endif

# endif

#endif
}

#endif



#ifdef IO_MATRIX__OUT__COLUMN3__PIN

#ifndef IO_MATRIX__IN__COLUMN3__STATE__REG
volatile uint8_t io_matrix__in__column3__state;
#endif

    void io_matrix__in__column3__state__update(void) {
#ifdef IO_MATRIX__IN__COLUMN3__STATE__REG
        __IN(io_matrix__in__column3__state, PIN_REG(SIGNAL_PORT(IO_MATRIX__IN)));

# ifdef IO_MATRIX__IN__ALT__PORT
        __IN(io_matrix__in__temp, PIN_REG(SIGNAL_PORT(IO_MATRIX__IN__ALT)));

#  ifdef IO_MATRIX__IN__ROW0__BIT
        COPY_BIT(io_matrix__in__temp, IO_MATRIX__IN__ROW0__PIN, io_matrix__in__column3__state, IO_MATRIX__IN__ROW0__BIT);
#  endif

#  ifdef IO_MATRIX__IN__ROW1__BIT
        COPY_BIT(io_matrix__in__temp, IO_MATRIX__IN__ROW1__PIN, io_matrix__in__column3__state, IO_MATRIX__IN__ROW1__BIT);
#  endif

#  ifdef IO_MATRIX__IN__ROW2__BIT
        COPY_BIT(io_matrix__in__temp, IO_MATRIX__IN__ROW2__PIN, io_matrix__in__column3__state, IO_MATRIX__IN__ROW2__BIT);
#  endif

#  ifdef IO_MATRIX__IN__ROW3__BIT
        COPY_BIT(io_matrix__in__temp, IO_MATRIX__IN__ROW3__PIN, io_matrix__in__column3__state, IO_MATRIX__IN__ROW3__BIT);
#  endif

#  ifdef IO_MATRIX__IN__ROW4__BIT
        COPY_BIT(io_matrix__in__temp, IO_MATRIX__IN__ROW4__PIN, io_matrix__in__column3__state, IO_MATRIX__IN__ROW4__BIT);
#  endif

#  ifdef IO_MATRIX__IN__ROW5__BIT
        COPY_BIT(io_matrix__in__temp, IO_MATRIX__IN__ROW5__PIN, io_matrix__in__column3__state, IO_MATRIX__IN__ROW5__BIT);
#  endif

#  ifdef IO_MATRIX__IN__ROW6__BIT
        COPY_BIT(io_matrix__in__temp, IO_MATRIX__IN__ROW6__PIN, io_matrix__in__column3__state, IO_MATRIX__IN__ROW6__BIT);
#  endif

#  ifdef IO_MATRIX__IN__ROW7__BIT
        COPY_BIT(io_matrix__in__temp, IO_MATRIX__IN__ROW7__PIN, io_matrix__in__column3__state, IO_MATRIX__IN__ROW7__BIT);
#  endif

# endif

#endif
    }

#endif


void io_matrix__in__init(void) {
        __asm__ __volatile__("io_matrix__in__init:");
#if defined(IO_MATRIX__IN__ROW0__PORT) && defined(IO_MATRIX__IN__ROW0__PIN)
        USE_PIN_AS_INPUT(IO_MATRIX__IN__ROW0__PORT, IO_MATRIX__IN__ROW0__PIN);
        ENABLE_PIN_PULLUP(IO_MATRIX__IN__ROW0__PORT, IO_MATRIX__IN__ROW0__PIN);
#endif
#if defined(IO_MATRIX__IN__ROW1__PORT) && defined(IO_MATRIX__IN__ROW1__PIN)
        USE_PIN_AS_INPUT(IO_MATRIX__IN__ROW1__PORT, IO_MATRIX__IN__ROW1__PIN);
        ENABLE_PIN_PULLUP(IO_MATRIX__IN__ROW1__PORT, IO_MATRIX__IN__ROW1__PIN);
#endif
#if defined(IO_MATRIX__IN__ROW2__PORT) && defined(IO_MATRIX__IN__ROW2__PIN)
        USE_PIN_AS_INPUT(IO_MATRIX__IN__ROW2__PORT, IO_MATRIX__IN__ROW2__PIN);
        ENABLE_PIN_PULLUP(IO_MATRIX__IN__ROW2__PORT, IO_MATRIX__IN__ROW2__PIN);
#endif
#if defined(IO_MATRIX__IN__ROW3__PORT) && defined(IO_MATRIX__IN__ROW3__PIN)
        USE_PIN_AS_INPUT(IO_MATRIX__IN__ROW3__PORT, IO_MATRIX__IN__ROW3__PIN);
        ENABLE_PIN_PULLUP(IO_MATRIX__IN__ROW3__PORT, IO_MATRIX__IN__ROW3__PIN);
#endif
#if defined(IO_MATRIX__IN__ROW4__PORT) && defined(IO_MATRIX__IN__ROW4__PIN)
        USE_PIN_AS_INPUT(IO_MATRIX__IN__ROW4__PORT, IO_MATRIX__IN__ROW4__PIN);
        ENABLE_PIN_PULLUP(IO_MATRIX__IN__ROW4__PORT, IO_MATRIX__IN__ROW4__PIN);
#endif
#if defined(IO_MATRIX__IN__ROW5__PORT) && defined(IO_MATRIX__IN__ROW5__PIN)
        USE_PIN_AS_INPUT(IO_MATRIX__IN__ROW5__PORT, IO_MATRIX__IN__ROW5__PIN);
        ENABLE_PIN_PULLUP(IO_MATRIX__IN__ROW5__PORT, IO_MATRIX__IN__ROW5__PIN);
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
