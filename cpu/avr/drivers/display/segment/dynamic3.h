// =============================================================================
// The driver for the 3-digit 7-segment multiplexed common-anode display.
// Provides basic operations, such as:
//
// - initialization of the segments port
// - turning the display on and off
// - selecting and deselecting individual digits
// - setting the value of segments to be displayed on selected digits.
// =============================================================================
#ifndef __CPU__AVR__DRIVERS__DISPLAY__SEGMENT__DYNAMIC3_H
#define __CPU__AVR__DRIVERS__DISPLAY__SEGMENT__DYNAMIC3_H

#include "device.h"
#include "cpu/avr/gpio.h"
#include <stdint.h>


inline void display_init(void) {
    USE_PORT_AS_OUTPUT(DISPLAY_SEGMENTS);
}

inline void display_on(void) {
    USE_AS_OUTPUT(DISPLAY_ANODE1);
    USE_AS_OUTPUT(DISPLAY_ANODE2);
    USE_AS_OUTPUT(DISPLAY_ANODE3);
}


inline void display_off(void) {
    USE_AS_INPUT(DISPLAY_ANODE1);
    USE_AS_INPUT(DISPLAY_ANODE2);
    USE_AS_INPUT(DISPLAY_ANODE3);
}


inline void display__segments__set(const uint8_t v)	{ OUT(DISPLAY_SEGMENTS, v); }


#define display_select_digit_1()	do {OUT_1(DISPLAY_ANODE1);} while(0)
#define display_deselect_digit_1()	do {OUT_0(DISPLAY_ANODE1);} while(0)

#define display_select_digit_2()	do {OUT_1(DISPLAY_ANODE2);} while(0)
#define display_deselect_digit_2()	do {OUT_0(DISPLAY_ANODE2);} while(0)

#define display_select_digit_3()	do {OUT_1(DISPLAY_ANODE3);} while(0)
#define display_deselect_digit_3()	do {OUT_0(DISPLAY_ANODE3);} while(0)


#endif