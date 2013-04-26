#include "util/hex.h"
#include <stdint.h>


/**
 * Parse a byte from hex string.
 * Only uppercase hex digits are recognized.
 * @param str the pointer to the string with 2 hex digits.
 * @return 16-bit result.
 *         the upper 8 bits is the status code: 0 means success, if bit 0 is set, the first digit is invalid; if bit 1 is set, the second digit is invalid; 
 *         the lower 8 bits is the parsed byte, which is valid if the status code is 0.
 */
uint16_t byte__parse_hex(const uint8_t* __restrict const str) {
    register uint8_t last_error = 0;
    register uint8_t c1 = str[0];
    if ((c1 < '0') || (c1 > 'F') || ((c1 > '9') && (c1 < 'A'))) last_error |= 1;

    register uint8_t c2 = str[1];
    if ((c2 < '0') || (c2 > 'F') || ((c2 > '9') && (c2 < 'A'))) last_error |= 2;

    register uint8_t x1 = ((c1 < 'A') ? (c1 & 0x0F) : (c1 - ('A' - 0x0A)));
    register uint8_t x2 = ((c2 < 'A') ? (c2 & 0x0F) : (c2 - ('A' - 0x0A)));

    return (last_error << 8) | (x1 << 4) | x2;
}
