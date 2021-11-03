// =============================================================================
// Driver for I/O matrix row driver pins.
// =============================================================================

#ifndef __DRIVERS__IO_MATRIX__OUT_ROWS_H
#define __DRIVERS__IO_MATRIX__OUT_ROWS_H

#include <stdbool.h>
#include <stdint.h>
#include "cpu/avr/gpio.h"


inline void io_matrix__out__row0__init(void) {
    USE_AS_OUTPUT(IO_MATRIX__OUT__ROW0);
}

inline void io_matrix__out__row1__init(void) {
    USE_AS_OUTPUT(IO_MATRIX__OUT__ROW1);
}

inline void io_matrix__out__row2__init(void) {
    USE_AS_OUTPUT(IO_MATRIX__OUT__ROW2);
}

inline void io_matrix__out__row3__init(void) {
    USE_AS_OUTPUT(IO_MATRIX__OUT__ROW3);
}

inline void io_matrix__out__row4__init(void) {
    USE_AS_OUTPUT(IO_MATRIX__OUT__ROW4);
}

inline void io_matrix__out__row5__init(void) {
    USE_AS_OUTPUT(IO_MATRIX__OUT__ROW5);
}

inline void io_matrix__out__row6__init(void) {
    USE_AS_OUTPUT(IO_MATRIX__OUT__ROW6);
}

inline void io_matrix__out__row7__init(void) {
    USE_AS_OUTPUT(IO_MATRIX__OUT__ROW7);
}


inline void io_matrix__out_rows__init(void) {
    io_matrix__out__row0__init();
    io_matrix__out__row1__init();
    io_matrix__out__row2__init();
    io_matrix__out__row3__init();
    io_matrix__out__row4__init();
    io_matrix__out__row5__init();
    io_matrix__out__row6__init();
    io_matrix__out__row7__init();
}


inline void io_matrix__out_rows__set(const uint8_t value) {
    OUT(IO_MATRIX__OUT__ROWS, value);
}

#endif