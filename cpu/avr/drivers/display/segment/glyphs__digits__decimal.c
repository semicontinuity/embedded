// =============================================================================
// The table of glyphs for decimal digits.
// Placed in RAM for speed.
// =============================================================================

#include "cpu/avr/drivers/display/segment/glyphs__digits.h"
#include "cpu/avr/drivers/display/segment/glyphs.h"

uint8_t const DIGITS[] = {
    DISPLAY_SEGMENT_GLYPH_0,
    DISPLAY_SEGMENT_GLYPH_1,
    DISPLAY_SEGMENT_GLYPH_2,
    DISPLAY_SEGMENT_GLYPH_3,
    DISPLAY_SEGMENT_GLYPH_4,
    DISPLAY_SEGMENT_GLYPH_5,
    DISPLAY_SEGMENT_GLYPH_6,
    DISPLAY_SEGMENT_GLYPH_7,
    DISPLAY_SEGMENT_GLYPH_8,
    DISPLAY_SEGMENT_GLYPH_9
};
