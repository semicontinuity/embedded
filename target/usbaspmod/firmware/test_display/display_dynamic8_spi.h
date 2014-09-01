// =============================================================================
// The driver for the 8-digit 7+DP-segment common anode? display,
// attached to SPI interface and the following pins:
//
// - DISPLAY_OE
// - DISPLAY_RCK
// =============================================================================
#ifndef __CPU__AVR__DRIVERS__DISPLAY__SEGMENT__STATIC2_SPI_H
#define __CPU__AVR__DRIVERS__DISPLAY__SEGMENT__STATIC2_SPI_H

#include "cpu/avr/gpio.h"
#include <stdint.h>

#include "cpu/avr/spi_polled.h"


inline void display__init(void) {
    USE_AS_OUTPUT(DISPLAY_OE);
    USE_AS_OUTPUT(DISPLAY_RCK);
    OUT_1(DISPLAY_RCK);
}

inline void display__on(void) {
    OUT_0(DISPLAY_OE);
}

inline void display__off(void) {
    OUT_1(DISPLAY_OE);
}


#endif