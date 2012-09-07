// =============================================================================
// Memory utilities
// =============================================================================

#ifndef __CPU_AVR_UTIL_MEMORY_H
#define __CPU_AVR_UTIL_MEMORY_H

#include <inttypes.h>
#include <stddef.h>
#include <avr/pgmspace.h>

#include "cpu/avr/asm.h"


#if defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__) ||\
    defined(__AVR_ATmega168__) 


inline static void memory__copy_P(void* dst, const void *src, uint8_t size) {
    while (1) {
        if (size == 0) break;
        ST_XPLUS(dst, __LPM_increment__(src));
        --size;
    }
    
}

#else

#   error "Unsupported MCU"

#endif

#endif