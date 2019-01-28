// =============================================================================
// ALARM line driver.
// =============================================================================

#ifndef __DRIVERS__OUT__ALARM_H
#define __DRIVERS__OUT__ALARM_H

#include <stdbool.h>
#include <stdint.h>
#include "cpu/avr/gpio.h"


inline void alarm__set(const uint8_t value) {
    if (value)
        OUT_1(ALARM);
    else
        OUT_0(ALARM);
}


/**
 * Initialize the ALARM line driver.
 * The out pin is forcibly driven low,
 * to ensure that alarm is off upon initialization.
 */
inline void alarm__init(void) {
    USE_AS_OUTPUT(ALARM);
    alarm__set(0);
}

#endif