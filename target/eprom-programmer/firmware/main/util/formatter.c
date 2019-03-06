#include "util/formatter.h"

/**
 * Converts a lowe nibble of a byte hex character.
 */
uint8_t formatter__nibble_to_hex_char(uint8_t value) {
    if (value > 9) value += ('A' - ('9' + 1));
    return value + '0';
}

/**
 * Converts a byte to 2 hex characters.
 */
uint16_t formatter__byte_to_hex_chars(const uint8_t value) {
    return (formatter__nibble_to_hex_char(value >> 4) << 8) | formatter__nibble_to_hex_char(value & 0x0F);
}
