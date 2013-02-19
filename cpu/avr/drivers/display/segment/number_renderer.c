// =============================================================================
// The number renderer for the 3-digit 7-segment multiplexed common-anode display.
// Provides operations for numeric display, such as:
//
// - rendering hex or bcd numbers for display on 7-segment display
// - adding comma to the specified digit
// =============================================================================

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

INLINE void number_renderer__render(const uint16_t number, uint8_t *buffer) {
    buffer[0] = DIGITS[(number >> 8) & 0x0F];
    buffer[1] = DIGITS[(number >> 4) & 0x0F];
    buffer[2] = DIGITS[number & 0x0F];
}

INLINE void number_renderer__render_decimal_point(uint8_t *buffer) {
    *buffer = DISPLAY_SEGMENT_VALUE_ADD_DP(*buffer);
}
