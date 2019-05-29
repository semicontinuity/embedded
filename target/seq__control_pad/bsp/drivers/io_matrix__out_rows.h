// =============================================================================
// Driver for I/O matrix output pins.
// =============================================================================

#ifndef __DRIVERS__IO_MATRIX__OUT_ROWS_H
#define __DRIVERS__IO_MATRIX__OUT_ROWS_H

#include <stdbool.h>
#include <stdint.h>
#include "cpu/avr/gpio.h"


inline void io_matrix__out_rows__set(const uint8_t value) {
    OUT(IO_MATRIX__OUT__ROWS, value);
}

inline void io_matrix__out_rows__init(void) {
#if defined(IO_MATRIX__OUT__ROW0__PORT) && defined(IO_MATRIX__OUT__ROW0__PIN)
    USE_AS_OUTPUT(IO_MATRIX__OUT__ROW0);
#endif
#if defined(IO_MATRIX__OUT__ROW1__PORT) && defined(IO_MATRIX__OUT__ROW1__PIN)
    USE_AS_OUTPUT(IO_MATRIX__OUT__ROW1);
#endif
#if defined(IO_MATRIX__OUT__ROW2__PORT) && defined(IO_MATRIX__OUT__ROW2__PIN)
    USE_AS_OUTPUT(IO_MATRIX__OUT__ROW2);
#endif
#if defined(IO_MATRIX__OUT__ROW3__PORT) && defined(IO_MATRIX__OUT__ROW3__PIN)
    USE_AS_OUTPUT(IO_MATRIX__OUT__ROW3);
#endif
#if defined(IO_MATRIX__OUT__ROW4__PORT) && defined(IO_MATRIX__OUT__ROW4__PIN)
    USE_AS_OUTPUT(IO_MATRIX__OUT__ROW4);
#endif
#if defined(IO_MATRIX__OUT__ROW5__PORT) && defined(IO_MATRIX__OUT__ROW5__PIN)
    USE_AS_OUTPUT(IO_MATRIX__OUT__ROW5);
#endif
#if defined(IO_MATRIX__OUT__ROW6__PORT) && defined(IO_MATRIX__OUT__ROW6__PIN)
    USE_AS_OUTPUT(IO_MATRIX__OUT__ROW6);
#endif
#if defined(IO_MATRIX__OUT__ROW7__PORT) && defined(IO_MATRIX__OUT__ROW7__PIN)
    USE_AS_OUTPUT(IO_MATRIX__OUT__ROW7);
#endif
}

#endif