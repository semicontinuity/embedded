// =============================================================================
// The driver for the 3-digit 7-segment multiplexed common-anode display.
// Provides operations for numeric display, such as:
//
// - displaying hex or bcd numbers
// - adding comma
// =============================================================================

#ifndef __DISPLAY_SEGMENT_3_NUMERIC_H
#define __DISPLAY_SEGMENT_3_NUMERIC_H

#include <stdint.h>

INLINE void numeric_display__set(const uint16_t number);
INLINE void numeric_display__add_comma_to_second_digit(void);

#endif