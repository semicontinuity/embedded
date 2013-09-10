// =============================================================================
// The driver for the 3-digit 7-segment multiplexed common-anode display.
// Provides operations for numeric display, such as:
//
// - displaying hex or bcd numbers
// - adding comma
// =============================================================================

#ifndef __CPU__AVR__DRIVERS__DISPLAY__SEGMENT__NUMBER_RENDERER_H
#define __CPU__AVR__DRIVERS__DISPLAY__SEGMENT__NUMBER_RENDERER_H

#include <stdint.h>

INLINE void number_renderer__render(const uint16_t number, uint8_t *buffer);
INLINE void number_renderer__render_decimal_point(uint8_t *buffer);

#endif