// =============================================================================
// Driver for I/O matrix column selector pins.
// =============================================================================

#ifndef __DRIVERS__IO_MATRIX__OUT_COLUMNS_H
#define __DRIVERS__IO_MATRIX__OUT_COLUMNS_H

#include <stdbool.h>
#include <stdint.h>
#include "cpu/avr/gpio.h"


inline void io_matrix__out__column0__init(void) {
    USE_AS_OUTPUT(IO_MATRIX__OUT__COLUMN0);
}

inline void io_matrix__out__column0__set(const uint8_t value) {
    if (value)
        OUT_1(IO_MATRIX__OUT__COLUMN0);
    else
        OUT_0(IO_MATRIX__OUT__COLUMN0);
}


inline void io_matrix__out__column1__init(void) {
    USE_AS_OUTPUT(IO_MATRIX__OUT__COLUMN1);
}

inline void io_matrix__out__column1__set(const uint8_t value) {
    if (value)
        OUT_1(IO_MATRIX__OUT__COLUMN1);
    else
        OUT_0(IO_MATRIX__OUT__COLUMN1);
}


inline void io_matrix__out__column2__init(void) {
    USE_AS_OUTPUT(IO_MATRIX__OUT__COLUMN2);
}

inline void io_matrix__out__column2__set(const uint8_t value) {
    if (value)
        OUT_1(IO_MATRIX__OUT__COLUMN2);
    else
        OUT_0(IO_MATRIX__OUT__COLUMN2);
}


inline void io_matrix__out__column3__init(void) {
    USE_AS_OUTPUT(IO_MATRIX__OUT__COLUMN3);
}

inline void io_matrix__out__column3__set(const uint8_t value) {
    if (value)
        OUT_1(IO_MATRIX__OUT__COLUMN3);
    else
        OUT_0(IO_MATRIX__OUT__COLUMN3);
}


void io_matrix__out_columns__init(void) {
    __asm__ __volatile__("io_matrix__out_columns__init:");
    io_matrix__out__column0__init();
    io_matrix__out__column1__init();
    io_matrix__out__column2__init();
    io_matrix__out__column3__init();
}


void io_matrix__out_columns__start(void) {
    __asm__ __volatile__("io_matrix__out_columns__start:");
    io_matrix__out__column0__set(0);
    io_matrix__out__column1__set(1);
    io_matrix__out__column2__set(1);
    io_matrix__out__column3__set(1);
}

#endif