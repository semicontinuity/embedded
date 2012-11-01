// =============================================================================
// Limited support for binary-to-bcd conversion.
// Used e.g. for printing decimal numbers, or displaying them on displays.
//
// Currently, only numbers in the range 0-511 are supported.
// =============================================================================

#ifndef __BCD_H
#define __BCD_H

#include <stdint.h>

/**
 * Converts the value (with the range 0-511) to BCD representation. 
 */
uint16_t uint9_to_bcd(const uint16_t number);

#endif