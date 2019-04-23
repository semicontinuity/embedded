// =============================================================================
// Driver for I/O matrix row driver pins.
// =============================================================================

#ifndef __DRIVERS__IO_MATRIX__OUT_ROWS_H
#define __DRIVERS__IO_MATRIX__OUT_ROWS_H

#include <stdbool.h>
#include <stdint.h>
#include "cpu/avr/gpio.h"


inline void led1r_row__init(void) {
    USE_AS_OUTPUT(OUT__LED1R_ROW);
}

inline void led1r_row__set(const uint8_t value) {
    if (value)
        OUT_1(OUT__LED1R_ROW);
    else
        OUT_0(OUT__LED1R_ROW);
}


inline void led1g_row__init(void) {
    USE_AS_OUTPUT(OUT__LED1G_ROW);
}

inline void led1g_row__set(const uint8_t value) {
    if (value)
        OUT_1(OUT__LED1G_ROW);
    else
        OUT_0(OUT__LED1G_ROW);
}


inline void led1b_row__init(void) {
    USE_AS_OUTPUT(OUT__LED1B_ROW);
}

inline void led1b_row__set(const uint8_t value) {
    if (value)
        OUT_1(OUT__LED1B_ROW);
    else
        OUT_0(OUT__LED1B_ROW);
}


inline void led2r_row__init(void) {
    USE_AS_OUTPUT(OUT__LED2R_ROW);
}

inline void led2r_row__set(const uint8_t value) {
    if (value)
        OUT_1(OUT__LED2R_ROW);
    else
        OUT_0(OUT__LED2R_ROW);
}


inline void led2g_row__init(void) {
    USE_AS_OUTPUT(OUT__LED2G_ROW);
}

inline void led2g_row__set(const uint8_t value) {
    if (value)
        OUT_1(OUT__LED2G_ROW);
    else
        OUT_0(OUT__LED2G_ROW);
}


inline void led2b_row__init(void) {
    USE_AS_OUTPUT(OUT__LED2B_ROW);
}

inline void led2b_row__set(const uint8_t value) {
    if (value)
        OUT_1(OUT__LED2B_ROW);
    else
        OUT_0(OUT__LED2B_ROW);
}


inline void buttons__leds_row__init(void) {
    USE_AS_OUTPUT(OUT__BUTTONS_LEDS_ROW);
}

inline void buttons__leds_row__set(const uint8_t value) {
    if (value)
        OUT_1(OUT__BUTTONS_LEDS_ROW);
    else
        OUT_0(OUT__BUTTONS_LEDS_ROW);
}


inline void io_matrix__out_rows__set(const uint8_t value) {
    OUT(IO_MATRIX__OUT__ROWS, value);
}

inline void io_matrix__out_rows__init(void) {
    led1b_row__init();
    led1g_row__init();
    led1r_row__init();

    led2b_row__init();
    led2g_row__init();
    led2r_row__init();

    buttons__leds_row__init();
}

#endif