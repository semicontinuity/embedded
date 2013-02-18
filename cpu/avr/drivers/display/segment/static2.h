// =============================================================================
// The driver for the 2-digit 7-segment common anode display,
// attached to SPI interface and the following pins:
//
// - DISPLAY_OE
// - DISPLAY_RESET
// - DISPLAY_RCK
// =============================================================================
#ifndef __CPU__AVR__DRIVERS__DISPLAY__SEGMENT__STATIC2_H
#define __CPU__AVR__DRIVERS__DISPLAY__SEGMENT__STATIC2_H

#include "cpu/avr/gpio.h"
#include <stdint.h>

#include "cpu/avr/spi_polled.h"


#define DISPLAY_SEGMENT_VALUE_0 0x21
#define DISPLAY_SEGMENT_VALUE_1 0xEB
#define DISPLAY_SEGMENT_VALUE_2 0x32
#define DISPLAY_SEGMENT_VALUE_3 0x62
#define DISPLAY_SEGMENT_VALUE_4 0xE8
#define DISPLAY_SEGMENT_VALUE_5 0x64
#define DISPLAY_SEGMENT_VALUE_6 0x24
#define DISPLAY_SEGMENT_VALUE_7 0xE3
#define DISPLAY_SEGMENT_VALUE_8 0x20
#define DISPLAY_SEGMENT_VALUE_9 0x60


inline void display__init(void) {
    USE_AS_OUTPUT(DISPLAY_OE);
    USE_AS_OUTPUT(DISPLAY_RESET);
    USE_AS_OUTPUT(DISPLAY_RCK);
    OUT_1(DISPLAY_RESET);
    OUT_1(DISPLAY_RCK);
}

inline void display__on(void) {
    OUT_0(DISPLAY_OE);
}

inline void display__off(void) {
    OUT_1(DISPLAY_OE);
}

/** Raw */
inline void display__set(const uint16_t v) {
    OUT_0(DISPLAY_RCK);
    spi__write(v >> 8);
    spi__write(v & 0xFF);
    OUT_1(DISPLAY_RCK);
}

INLINE void display__render(const uint8_t bcd);

#endif