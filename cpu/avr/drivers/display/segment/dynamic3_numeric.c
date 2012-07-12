// =============================================================================
// The driver for the 3-digit 7-segment multiplexed common-anode display.
// Provides operations for numeric display, such as:
//
// - displaying hex or bcd numbers
// - adding comma
//
// TODO: replace hardcoded reference display_thread__segments with pointer
// =============================================================================

#include "device.h"

#include "cpu/avr/drivers/display/segment/dynamic3_numeric.h"
#include "cpu/avr/drivers/display/segment/dynamic3_thread.h"
#include "cpu/avr/drivers/display/segment/values.h"

uint8_t const DIGITS[] = {
    DISPLAY_SEGMENT_VALUE_0,
    DISPLAY_SEGMENT_VALUE_1,
    DISPLAY_SEGMENT_VALUE_2,
    DISPLAY_SEGMENT_VALUE_3,
    DISPLAY_SEGMENT_VALUE_4,
    DISPLAY_SEGMENT_VALUE_5,
    DISPLAY_SEGMENT_VALUE_6,
    DISPLAY_SEGMENT_VALUE_7,
    DISPLAY_SEGMENT_VALUE_8,
    DISPLAY_SEGMENT_VALUE_9,

    DISPLAY_SEGMENT_VALUE_A,
    DISPLAY_SEGMENT_VALUE_b,
    DISPLAY_SEGMENT_VALUE_C,
    DISPLAY_SEGMENT_VALUE_d,
    DISPLAY_SEGMENT_VALUE_E,
    DISPLAY_SEGMENT_VALUE_F
};

INLINE void numeric_display__set(const uint16_t number) {
    display_thread__segments[0] = DIGITS[(number >> 8) & 0x0F];
    display_thread__segments[1] = DIGITS[(number >> 4) & 0x0F];
    display_thread__segments[2] = DIGITS[number & 0x0F];
}

INLINE void numeric_display__add_comma_to_second_digit(void) {
    display_thread__segments[1] = DISPLAY_SEGMENT_VALUE_ADD_DP(display_thread__segments[1]);
}
