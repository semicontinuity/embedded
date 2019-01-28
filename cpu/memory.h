// Portability layer for memory operations
//
// Defines:
//
// PROGMEM


#ifndef __CPU__MEMORY_H
#define __CPU__MEMORY_H

#if defined(__AVR__)

#   include <avr/pgmspace.h>

#else

#   error "Unsupported MCU"

#endif

#endif