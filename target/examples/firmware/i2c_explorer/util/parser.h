#ifndef __UTIL__PARSER_H
#define __UTIL__PARSER_H

#include <stdint.h>

uint16_t parser__parse_hex_chars(uint8_t c1, uint8_t c2);

uint16_t parser__parse_hex_byte(const uint8_t* __restrict str);

#endif