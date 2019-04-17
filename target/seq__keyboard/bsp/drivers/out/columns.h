// =============================================================================
// Driver for column selector pins.
// =============================================================================

#ifndef __DRIVERS__OUT__COLUMNS_H
#define __DRIVERS__OUT__COLUMNS_H

#include <stdbool.h>
#include <stdint.h>
#include "cpu/avr/gpio.h"


inline void column0__init(void) {
    USE_AS_OUTPUT(OUT__COLUMN0);
}

inline void column0__set(const uint8_t value) {
    if (value)
        OUT_1(OUT__COLUMN0);
    else
        OUT_0(OUT__COLUMN0);
}


inline void column1__init(void) {
    USE_AS_OUTPUT(OUT__COLUMN1);
}

inline void column1__set(const uint8_t value) {
    if (value)
        OUT_1(OUT__COLUMN1);
    else
        OUT_0(OUT__COLUMN1);
}


inline void column2__init(void) {
    USE_AS_OUTPUT(OUT__COLUMN2);
}

inline void column2__set(const uint8_t value) {
    if (value)
        OUT_1(OUT__COLUMN2);
    else
        OUT_0(OUT__COLUMN2);
}


inline void column3__init(void) {
    USE_AS_OUTPUT(OUT__COLUMN3);
}

inline void column3__set(const uint8_t value) {
    if (value)
        OUT_1(OUT__COLUMN3);
    else
        OUT_0(OUT__COLUMN3);
}

#endif