// =============================================================================
// Driver for I/O matrix column selector pins.
// =============================================================================

#ifndef __DRIVERS__IO_MATRIX__OUT_COLUMNS_H
#define __DRIVERS__IO_MATRIX__OUT_COLUMNS_H

#include <stdbool.h>
#include <stdint.h>
#include "cpu/avr/gpio.h"


#if defined(IO_MATRIX__OUT__COLUMN0__PORT) && defined(IO_MATRIX__OUT__COLUMN0__PIN)
inline void io_matrix__out__column0__init(void) {
    USE_AS_OUTPUT(IO_MATRIX__OUT__COLUMN0);
}

inline void io_matrix__out__column0__set(const uint8_t value) {
    if (value)
        OUT_1(IO_MATRIX__OUT__COLUMN0);
    else
        OUT_0(IO_MATRIX__OUT__COLUMN0);
}
#endif


#if defined(IO_MATRIX__OUT__COLUMN1__PORT) && defined(IO_MATRIX__OUT__COLUMN1__PIN)
inline void io_matrix__out__column1__init(void) {
    USE_AS_OUTPUT(IO_MATRIX__OUT__COLUMN1);
}

inline void io_matrix__out__column1__set(const uint8_t value) {
    if (value)
        OUT_1(IO_MATRIX__OUT__COLUMN1);
    else
        OUT_0(IO_MATRIX__OUT__COLUMN1);
}
#endif


#if defined(IO_MATRIX__OUT__COLUMN2__PORT) && defined(IO_MATRIX__OUT__COLUMN2__PIN)
inline void io_matrix__out__column2__init(void) {
    USE_AS_OUTPUT(IO_MATRIX__OUT__COLUMN2);
}

inline void io_matrix__out__column2__set(const uint8_t value) {
    if (value)
        OUT_1(IO_MATRIX__OUT__COLUMN2);
    else
        OUT_0(IO_MATRIX__OUT__COLUMN2);
}
#endif


#if defined(IO_MATRIX__OUT__COLUMN3__PORT) && defined(IO_MATRIX__OUT__COLUMN3__PIN)
inline void io_matrix__out__column3__init(void) {
    USE_AS_OUTPUT(IO_MATRIX__OUT__COLUMN3);
}

inline void io_matrix__out__column3__set(const uint8_t value) {
    if (value)
        OUT_1(IO_MATRIX__OUT__COLUMN3);
    else
        OUT_0(IO_MATRIX__OUT__COLUMN3);
}
#endif


void io_matrix__out_columns__init(void) {
    __asm__ __volatile__("io_matrix__out_columns__init:");
#if defined(IO_MATRIX__OUT__COLUMN0__PORT) && defined(IO_MATRIX__OUT__COLUMN0__PIN)
    io_matrix__out__column0__init();
#endif
#if defined(IO_MATRIX__OUT__COLUMN1__PORT) && defined(IO_MATRIX__OUT__COLUMN1__PIN)
    io_matrix__out__column1__init();
#endif
#if defined(IO_MATRIX__OUT__COLUMN2__PORT) && defined(IO_MATRIX__OUT__COLUMN2__PIN)
    io_matrix__out__column2__init();
#endif
#if defined(IO_MATRIX__OUT__COLUMN3__PORT) && defined(IO_MATRIX__OUT__COLUMN3__PIN)
    io_matrix__out__column3__init();
#endif
}


void io_matrix__out_columns__start(void) {
    __asm__ __volatile__("io_matrix__out_columns__start:");
#if defined(IO_MATRIX__OUT__COLUMN0__PORT) && defined(IO_MATRIX__OUT__COLUMN0__PIN)
    io_matrix__out__column0__set(0);
#endif
#if defined(IO_MATRIX__OUT__COLUMN1__PORT) && defined(IO_MATRIX__OUT__COLUMN1__PIN)
    io_matrix__out__column1__set(0);
#endif
#if defined(IO_MATRIX__OUT__COLUMN2__PORT) && defined(IO_MATRIX__OUT__COLUMN2__PIN)
    io_matrix__out__column2__set(0);
#endif
#if defined(IO_MATRIX__OUT__COLUMN3__PORT) && defined(IO_MATRIX__OUT__COLUMN3__PIN)
    io_matrix__out__column3__set(0);
#endif
}

#endif