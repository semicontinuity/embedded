#include <avr/io.h>

/**
 * Parses 2-byte string with hex byte.
 * @returns 16-bit value: upper byte is 0 if parsed successfully, lower byte contains parsed value
 */
uint16_t parser__parse_hex_byte(const uint8_t* __restrict const str) {
    uint8_t c1 = str[0];
    if ((c1 < '0') || (c1 > 'F') || ((c1 > '9') && (c1 < 'A'))) return 0xFF00;

    uint8_t c2 = str[1];
    if ((c2 < '0') || (c2 > 'F') || ((c2 > '9') && (c2 < 'A'))) return 0xFF00;

    uint8_t x1 = ((c1 < 'A') ? (c1 & 0x0F) : (c1 - ('A' - 0x0A)));
    uint8_t x2 = ((c2 < 'A') ? (c2 & 0x0F) : (c2 - ('A' - 0x0A)));
    return (x1 << 4) | x2;
}
