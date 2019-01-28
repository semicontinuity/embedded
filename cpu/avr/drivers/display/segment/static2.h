// =============================================================================
// The driver for the 2-digit 7-segment common anode display,
// attached to 2 MCU ports DISPLAY_DIGIT1 and DISPLAY_DIGIT0
// =============================================================================
#ifndef __CPU__AVR__DRIVERS__DISPLAY__SEGMENT__STATIC2_H
#define __CPU__AVR__DRIVERS__DISPLAY__SEGMENT__STATIC2_H

#include "cpu/avr/gpio.h"
#include "cpu/avr/drivers/display/segment/glyphs__digits.h"
#include <stdint.h>


/** Initialize display */
void display__init(void);


/** Output raw data, every bit corresponds to a segment */
void display__set(const uint16_t v);


/**
 * Output packed data, every nibble corresponds to a digit.
 * Suitable for rendering of hexadecimal and BCD numbers.
 */
void display__render_packed(const uint8_t packed);

void display__digits__0__add_dp(void);


#endif