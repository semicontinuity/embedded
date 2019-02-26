// =============================================================================
// The driver for the 7-segment common-anode display.
// Provides the values of some basic glyphs that can be displayed.
//
// Requires the following macros to be defined:
//
// - DISPLAY_SEGMENT_A__PIN
// - DISPLAY_SEGMENT_B__PIN
// - DISPLAY_SEGMENT_C__PIN
// - DISPLAY_SEGMENT_D__PIN
// - DISPLAY_SEGMENT_E__PIN
// - DISPLAY_SEGMENT_F__PIN
// - DISPLAY_SEGMENT_G__PIN
// - DISPLAY_SEGMENT_DP__PIN
//
// The values for the pins can be different on different platforms (boards),
// they depend on the board layout.
// =============================================================================

#ifndef __CPU__AVR__DRIVERS__DISPLAY__SEGMENT__GLYPHS_H
#define __CPU__AVR__DRIVERS__DISPLAY__SEGMENT__GLYPHS_H

#include <stdint.h>
#include "cpu/avr/gpio.h"


#define DISPLAY_SEGMENT_GLYPH_EMPTY	(~0)

#define DISPLAY_SEGMENT_GLYPH_0	((uint8_t)~(\
    SIGNAL_MASK(DISPLAY_SEGMENT_A)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_B)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_C)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_D)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_E)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_F)	))

#define DISPLAY_SEGMENT_GLYPH_1	((uint8_t)~(\
    SIGNAL_MASK(DISPLAY_SEGMENT_B)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_C)	))

#define DISPLAY_SEGMENT_GLYPH_2	((uint8_t)~(\
    SIGNAL_MASK(DISPLAY_SEGMENT_A)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_B)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_D)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_E)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_G)	))

#define DISPLAY_SEGMENT_GLYPH_3	((uint8_t)~(\
    SIGNAL_MASK(DISPLAY_SEGMENT_A)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_B)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_C)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_D)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_G)	))

#define DISPLAY_SEGMENT_GLYPH_4	((uint8_t)~(\
    SIGNAL_MASK(DISPLAY_SEGMENT_B)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_C)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_F)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_G)	))

#define DISPLAY_SEGMENT_GLYPH_5	((uint8_t)~(\
    SIGNAL_MASK(DISPLAY_SEGMENT_A)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_C)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_D)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_F)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_G)	))

#define DISPLAY_SEGMENT_GLYPH_6	((uint8_t)~(\
    SIGNAL_MASK(DISPLAY_SEGMENT_A)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_C)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_D)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_E)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_F)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_G)	))

#define DISPLAY_SEGMENT_GLYPH_7	((uint8_t)~(\
    SIGNAL_MASK(DISPLAY_SEGMENT_A)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_B)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_C)	))

#define DISPLAY_SEGMENT_GLYPH_8	((uint8_t)~(\
    SIGNAL_MASK(DISPLAY_SEGMENT_A)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_B)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_C)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_D)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_E)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_F)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_G)	))

#define DISPLAY_SEGMENT_GLYPH_9	((uint8_t)~(\
    SIGNAL_MASK(DISPLAY_SEGMENT_A)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_B)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_C)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_D)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_F)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_G)	))

#define DISPLAY_SEGMENT_GLYPH_A	((uint8_t)~(\
    SIGNAL_MASK(DISPLAY_SEGMENT_A)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_B)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_C)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_E)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_F)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_G)	))

#define DISPLAY_SEGMENT_GLYPH_b	((uint8_t)~(\
    SIGNAL_MASK(DISPLAY_SEGMENT_C)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_D)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_E)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_F)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_G)	))

#define DISPLAY_SEGMENT_GLYPH_C	((uint8_t)~(\
    SIGNAL_MASK(DISPLAY_SEGMENT_A)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_D)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_E)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_F)	))

#define DISPLAY_SEGMENT_GLYPH_d	((uint8_t)~(\
    SIGNAL_MASK(DISPLAY_SEGMENT_B)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_C)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_D)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_E)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_G)	))

#define DISPLAY_SEGMENT_GLYPH_E	((uint8_t)~(\
    SIGNAL_MASK(DISPLAY_SEGMENT_A)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_D)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_E)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_F)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_G)	))

#define DISPLAY_SEGMENT_GLYPH_F	((uint8_t)~(\
    SIGNAL_MASK(DISPLAY_SEGMENT_A)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_E)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_F)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_G)	))

#define DISPLAY_SEGMENT_GLYPH_H	((uint8_t)~(\
    SIGNAL_MASK(DISPLAY_SEGMENT_B)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_C)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_E)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_F)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_G)	))

#define DISPLAY_SEGMENT_GLYPH_P	((uint8_t)~(\
    SIGNAL_MASK(DISPLAY_SEGMENT_A)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_B)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_E)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_F)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_G)	))

#define DISPLAY_SEGMENT_GLYPH_n	((uint8_t)~(\
    SIGNAL_MASK(DISPLAY_SEGMENT_C)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_E)	|\
    SIGNAL_MASK(DISPLAY_SEGMENT_G)	))

#define DISPLAY_SEGMENT_GLYPH_MINUS	((uint8_t)~SIGNAL_MASK(DISPLAY_SEGMENT_G))

#define DISPLAY_SEGMENT_GLYPH_ADD_DP(v) ((v) & ((uint8_t)~SIGNAL_MASK(DISPLAY_SEGMENT_DP)))


#endif