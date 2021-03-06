#ifndef __DEBUG_H
#define __DEBUG_H

#include <stdint.h>
#include <avr/pgmspace.h>

// The user must define "DEBUG_IMPL_H" and "debug__putc" that prints one character debug output
#if !defined(DEBUG_IMPL_H)
# include "cpu/avr/usart0.h"
# include "cpu/avr/usart0__rx_polled.h"
# include "cpu/avr/usart0__tx_polled.h"

# if !defined(debug__putc)
#  include "cpu/avr/usart0__tx_polled.h"
#  define debug__putc usart0__out__write
# endif

# if !defined(debug__in__read)
#  include "cpu/avr/usart0__rx_polled.h"
#  define debug__in__read usart0__in__read
# endif

#endif


void debug__print_P(const char * PROGMEM buffer);
void debug__print_string_progmem(const char * PROGMEM buffer);
void debug__print_byte_as_hex(uint8_t value);

#endif
