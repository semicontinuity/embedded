#ifndef __DEBUG_H
#define __DEBUG_H

#include <stdint.h>
#include <avr/pgmspace.h>

// The user must define "DEBUG_IMPL_H" and "debug__putc" that prints one character debug output
#if !defined(DEBUG_IMPL_H)
# if !defined(debug__putc)
#  define debug__putc usart0__out__write
# endif
# include "cpu/avr/usart0.h"
# include "cpu/avr/usart0__tx_polled.h"
#endif


void debug__print_string_progmem(const char *str);
void debug__print_byte_as_hex(uint8_t value);



inline uint8_t debug__lower_nibble_to_hex(uint8_t value) {
    if (value > 9) value += ('A' - ('9' + 1));
    return value += '0';
}

#endif
