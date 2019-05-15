// =============================================================================
// Alarm (Interrupt OUT) line driver.
// =============================================================================

#ifndef __DRIVERS__OUT__ALARM_H
#define __DRIVERS__OUT__ALARM_H

#include <stdbool.h>
#include <stdint.h>
#include "cpu/avr/gpio.h"


/**
 * Toggle ALARM.
 */
inline void alarm__toggle(void) {
    TOGGLE(OUT__ALARM);
}


/**
 * Set ALARM value.
 */
inline void alarm__set(const uint8_t value) {
    if (value)
        OUT_1(OUT__ALARM);
    else
        OUT_0(OUT__ALARM);
}


/**
 * Get ALARM value.
 */
inline bool alarm__get(void) {
    return (bool) IS_OUT_1(OUT__ALARM);
}


/**
 * Initialize ALARM line driver.
 */
inline void alarm__init(void) {
    USE_AS_OUTPUT(OUT__ALARM);
}

#endif