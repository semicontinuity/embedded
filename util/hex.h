#ifndef __UTIL__HEX_H
#define __UTIL__HEX_H

#include <avr/io.h>


/**
 * Parse a byte from hex string.
 * Only uppercase hex digits are recognized.
 * @param str the pointer to the string with 2 hex digits.
 * @return 16-bit result.
 *         the upper 8 bits is the status code: 0 means success, if bit 0 is set, the first digit is invalid; if bit 1 is set, the second digit is invalid; 
 *         the lower 8 bits is the parsed byte, which is valid if the status code is 0.
 */
uint16_t byte__parse_hex(const uint8_t* __restrict const str);

#endif