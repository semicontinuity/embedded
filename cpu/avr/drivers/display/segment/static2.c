// =============================================================================
// The driver for the 2-digit 7-segment common anode display,
// attached to 2 MCU ports DISPLAY_DIGIT1 and DISPLAY_DIGIT0
// =============================================================================

#include "cpu/avr/drivers/display/segment/static2.h"
#include "cpu/avr/drivers/display/segment/glyphs__digits.h"


/** Initialize display */
void display__init(void) {
    USE_PORT_AS_OUTPUT(DISPLAY_DIGIT1);
    USE_PORT_AS_OUTPUT(DISPLAY_DIGIT0);
}

/** Output raw data, every bit corresponds to a segment */
void display__set(const uint16_t v) {
    OUT(DISPLAY_DIGIT1, v >> 8);
    OUT(DISPLAY_DIGIT0, v & 0xFF);
}

/**
 * Output packed data, every nibble corresponds to a digit.
 * Suitable for rendering of hexadecimal and BCD numbers.
 */
void display__render_packed(const uint8_t packed) {
    display__set(((DIGITS[(packed >> 4) & 0x0F]) << 8) | DIGITS[packed & 0x0F]);
}

void display__digits__0__add_dp(void) {
    OUT(DISPLAY_DIGIT0, DISPLAY_SEGMENT_GLYPH_ADD_DP(PORT_VALUE(DISPLAY_DIGIT0)));
}
