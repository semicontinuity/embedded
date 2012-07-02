#ifndef __DEBUG_H
#define __DEBUG_H

#include <stdint.h>
#include <avr/pgmspace.h>

void debug__print_string_progmem(const char *str);
void debug__print_byte_as_hex(uint8_t value);

#endif
