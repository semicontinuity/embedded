#ifndef __UTIL__FORMATTER_H
#define __UTIL__FORMATTER_H

#include <stdint.h>

/**
 * Converts a lower nibble of a byte hex character.
 */
uint8_t formatter__nibble_to_hex_char(const uint8_t value);

/**
 * Converts a byte to 2 hex characters.
 */
uint16_t formatter__byte_to_hex_chars(const uint8_t value);

#endif