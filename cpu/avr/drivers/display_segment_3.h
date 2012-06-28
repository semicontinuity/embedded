// =============================================================================
// The driver for the 3-digit 7-segment multiplexed common-anode display.
// Provides basic operations, such as:
//
// - initialization of the segments port
// - turning the display on and off
// - selecting and deselecting individual digits
// - setting the value of segments to be displayed on selected digits.
// =============================================================================
#ifndef __DISPLAY_SEGMENT_3_H
#define __DISPLAY_SEGMENT_3_H

#include "device.h"
#include "cpu/avr/gpio.h"
#include <stdint.h>


inline void display_init(void) {
    DISPLAY_SEGMENTS_DIR  = 0xFF;
}

inline void display_on(void) {
    CONFIGURE_AS_OUTPUT(DISPLAY_ANODE1);
    CONFIGURE_AS_OUTPUT(DISPLAY_ANODE2);
    CONFIGURE_AS_OUTPUT(DISPLAY_ANODE3);
}


inline void display_off(void) {
    CONFIGURE_AS_INPUT(DISPLAY_ANODE1);
    CONFIGURE_AS_INPUT(DISPLAY_ANODE2);
    CONFIGURE_AS_INPUT(DISPLAY_ANODE3);
}


inline void display__segments__set(uint8_t v)	{ DISPLAY_SEGMENTS_PORT = v; }


#define display_select_digit_1()	do {DRIVE_HIGH(DISPLAY_ANODE1);} while(0)
#define display_deselect_digit_1()	do {DRIVE_LOW(DISPLAY_ANODE1);} while(0)

#define display_select_digit_2()	do {DRIVE_HIGH(DISPLAY_ANODE2);} while(0)
#define display_deselect_digit_2()	do {DRIVE_LOW(DISPLAY_ANODE2);} while(0)

#define display_select_digit_3()	do {DRIVE_HIGH(DISPLAY_ANODE3);} while(0)
#define display_deselect_digit_3()	do {DRIVE_LOW(DISPLAY_ANODE3);} while(0)


#endif