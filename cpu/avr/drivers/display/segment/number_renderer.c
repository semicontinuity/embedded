// =============================================================================
// The number renderer for the 3-digit 7-segment multiplexed common-anode display.
// Provides operations for numeric display, such as:
//
// - rendering hex or bcd numbers for display on 7-segment display
// - adding comma to the specified digit
// =============================================================================

#include "cpu/avr/drivers/display/segment/glyphs.h"
#include "cpu/avr/drivers/display/segment/glyphs__digits.h"


INLINE void number_renderer__render(const uint16_t number, uint8_t *buffer) {
    buffer[0] = DIGITS[(number >> 8) & 0x0F];
    buffer[1] = DIGITS[(number >> 4) & 0x0F];
    buffer[2] = DIGITS[number & 0x0F];
}

INLINE void number_renderer__render_decimal_point(uint8_t *buffer) {
    *buffer = DISPLAY_SEGMENT_GLYPH_ADD_DP(*buffer);
}
