// =============================================================================
// Driver for rows with LEDs.
// =============================================================================

#ifndef __DRIVERS__OUT__LEDS_ROWS_H
#define __DRIVERS__OUT__LEDS_ROWS_H

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

#endif
