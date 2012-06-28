// =============================================================================
// The driver for the 7-segment common-anode display.
// Provides the values of some basic glyphs that can be displayed.
//
// Requires the following macros to be defined:
//
// - DISPLAY_SEGMENTS_PORT
// - DISPLAY_SEGMENTS_DIR

// - DISPLAY_SEGMENT_A_PIN
// - DISPLAY_SEGMENT_B_PIN
// - DISPLAY_SEGMENT_C_PIN
// - DISPLAY_SEGMENT_D_PIN
// - DISPLAY_SEGMENT_E_PIN
// - DISPLAY_SEGMENT_F_PIN
// - DISPLAY_SEGMENT_G_PIN
// - DISPLAY_SEGMENT_DP_PIN
//
// The values for the pins can be different on different platforms (boards),
// they depent on the board layout.
// =============================================================================

#ifndef __DISPLAY_SEGMENT_H
#define __DISPLAY_SEGMENT_H

#include "device.h"
#include <stdint.h>


#define DISPLAY_SEGMENT_VALUE_EMPTY	(~0)

#define DISPLAY_SEGMENT_VALUE_0	(~(\
    _BV(DISPLAY_SEGMENT_A_PIN)	|\
    _BV(DISPLAY_SEGMENT_B_PIN)	|\
    _BV(DISPLAY_SEGMENT_C_PIN)	|\
    _BV(DISPLAY_SEGMENT_D_PIN)	|\
    _BV(DISPLAY_SEGMENT_E_PIN)	|\
    _BV(DISPLAY_SEGMENT_F_PIN)	))

#define DISPLAY_SEGMENT_VALUE_1	(~(\
    _BV(DISPLAY_SEGMENT_B_PIN)	|\
    _BV(DISPLAY_SEGMENT_C_PIN)	))

#define DISPLAY_SEGMENT_VALUE_2	(~(\
    _BV(DISPLAY_SEGMENT_A_PIN)	|\
    _BV(DISPLAY_SEGMENT_B_PIN)	|\
    _BV(DISPLAY_SEGMENT_D_PIN)	|\
    _BV(DISPLAY_SEGMENT_E_PIN)	|\
    _BV(DISPLAY_SEGMENT_G_PIN)	))

#define DISPLAY_SEGMENT_VALUE_3	(~(\
    _BV(DISPLAY_SEGMENT_A_PIN)	|\
    _BV(DISPLAY_SEGMENT_B_PIN)	|\
    _BV(DISPLAY_SEGMENT_C_PIN)	|\
    _BV(DISPLAY_SEGMENT_D_PIN)	|\
    _BV(DISPLAY_SEGMENT_G_PIN)	))

#define DISPLAY_SEGMENT_VALUE_4	(~(\
    _BV(DISPLAY_SEGMENT_B_PIN)	|\
    _BV(DISPLAY_SEGMENT_C_PIN)	|\
    _BV(DISPLAY_SEGMENT_F_PIN)	|\
    _BV(DISPLAY_SEGMENT_G_PIN)	))

#define DISPLAY_SEGMENT_VALUE_5	(~(\
    _BV(DISPLAY_SEGMENT_A_PIN)	|\
    _BV(DISPLAY_SEGMENT_C_PIN)	|\
    _BV(DISPLAY_SEGMENT_D_PIN)	|\
    _BV(DISPLAY_SEGMENT_F_PIN)	|\
    _BV(DISPLAY_SEGMENT_G_PIN)	))

#define DISPLAY_SEGMENT_VALUE_6	(~(\
    _BV(DISPLAY_SEGMENT_A_PIN)	|\
    _BV(DISPLAY_SEGMENT_C_PIN)	|\
    _BV(DISPLAY_SEGMENT_D_PIN)	|\
    _BV(DISPLAY_SEGMENT_E_PIN)	|\
    _BV(DISPLAY_SEGMENT_F_PIN)	|\
    _BV(DISPLAY_SEGMENT_G_PIN)	))

#define DISPLAY_SEGMENT_VALUE_7	(~(\
    _BV(DISPLAY_SEGMENT_A_PIN)	|\
    _BV(DISPLAY_SEGMENT_B_PIN)	|\
    _BV(DISPLAY_SEGMENT_C_PIN)	))

#define DISPLAY_SEGMENT_VALUE_8	(~(\
    _BV(DISPLAY_SEGMENT_A_PIN)	|\
    _BV(DISPLAY_SEGMENT_B_PIN)	|\
    _BV(DISPLAY_SEGMENT_C_PIN)	|\
    _BV(DISPLAY_SEGMENT_D_PIN)	|\
    _BV(DISPLAY_SEGMENT_E_PIN)	|\
    _BV(DISPLAY_SEGMENT_F_PIN)	|\
    _BV(DISPLAY_SEGMENT_G_PIN)	))

#define DISPLAY_SEGMENT_VALUE_9	(~(\
    _BV(DISPLAY_SEGMENT_A_PIN)	|\
    _BV(DISPLAY_SEGMENT_B_PIN)	|\
    _BV(DISPLAY_SEGMENT_C_PIN)	|\
    _BV(DISPLAY_SEGMENT_D_PIN)	|\
    _BV(DISPLAY_SEGMENT_F_PIN)	|\
    _BV(DISPLAY_SEGMENT_G_PIN)	))

#define DISPLAY_SEGMENT_VALUE_A	(~(\
    _BV(DISPLAY_SEGMENT_A_PIN)	|\
    _BV(DISPLAY_SEGMENT_B_PIN)	|\
    _BV(DISPLAY_SEGMENT_C_PIN)	|\
    _BV(DISPLAY_SEGMENT_E_PIN)	|\
    _BV(DISPLAY_SEGMENT_F_PIN)	|\
    _BV(DISPLAY_SEGMENT_G_PIN)	))

#define DISPLAY_SEGMENT_VALUE_b	(~(\
    _BV(DISPLAY_SEGMENT_C_PIN)	|\
    _BV(DISPLAY_SEGMENT_D_PIN)	|\
    _BV(DISPLAY_SEGMENT_E_PIN)	|\
    _BV(DISPLAY_SEGMENT_F_PIN)	|\
    _BV(DISPLAY_SEGMENT_G_PIN)	))

#define DISPLAY_SEGMENT_VALUE_C	(~(\
    _BV(DISPLAY_SEGMENT_A_PIN)	|\
    _BV(DISPLAY_SEGMENT_D_PIN)	|\
    _BV(DISPLAY_SEGMENT_E_PIN)	|\
    _BV(DISPLAY_SEGMENT_F_PIN)	))

#define DISPLAY_SEGMENT_VALUE_d	(~(\
    _BV(DISPLAY_SEGMENT_B_PIN)	|\
    _BV(DISPLAY_SEGMENT_C_PIN)	|\
    _BV(DISPLAY_SEGMENT_D_PIN)	|\
    _BV(DISPLAY_SEGMENT_E_PIN)	|\
    _BV(DISPLAY_SEGMENT_G_PIN)	))

#define DISPLAY_SEGMENT_VALUE_E	(~(\
    _BV(DISPLAY_SEGMENT_A_PIN)	|\
    _BV(DISPLAY_SEGMENT_D_PIN)	|\
    _BV(DISPLAY_SEGMENT_E_PIN)	|\
    _BV(DISPLAY_SEGMENT_F_PIN)	|\
    _BV(DISPLAY_SEGMENT_G_PIN)	))

#define DISPLAY_SEGMENT_VALUE_F	(~(\
    _BV(DISPLAY_SEGMENT_A_PIN)	|\
    _BV(DISPLAY_SEGMENT_E_PIN)	|\
    _BV(DISPLAY_SEGMENT_F_PIN)	|\
    _BV(DISPLAY_SEGMENT_G_PIN)	))

#define DISPLAY_SEGMENT_VALUE_H	(~(\
    _BV(DISPLAY_SEGMENT_B_PIN)	|\
    _BV(DISPLAY_SEGMENT_C_PIN)	|\
    _BV(DISPLAY_SEGMENT_E_PIN)	|\
    _BV(DISPLAY_SEGMENT_F_PIN)	|\
    _BV(DISPLAY_SEGMENT_G_PIN)	))

#define DISPLAY_SEGMENT_VALUE_P	(~(\
    _BV(DISPLAY_SEGMENT_A_PIN)	|\
    _BV(DISPLAY_SEGMENT_B_PIN)	|\
    _BV(DISPLAY_SEGMENT_E_PIN)	|\
    _BV(DISPLAY_SEGMENT_F_PIN)	|\
    _BV(DISPLAY_SEGMENT_G_PIN)	))

#define DISPLAY_SEGMENT_VALUE_MINUS	(~_BV(DISPLAY_SEGMENT_G_PIN))

#define DISPLAY_SEGMENT_VALUE_ADD_DP(v) ((v) &= (~_BV(DISPLAY_SEGMENT_DP_PIN)))

#endif