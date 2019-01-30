// =============================================================================
// Flash driver
// procedures are inlineable, so it is easier to place them
// at the desired address during linking (hard with avr-libc)
// =============================================================================

#ifndef __CPU_AVR_FLASH_H
#define __CPU_AVR_FLASH_H

#include <stdbool.h>
#include <avr/io.h>


#if defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__) ||\
    defined(__AVR_ATmega168__) ||\
    defined(__AVR_ATmega8__) || defined(__AVR_ATmega16__)


#if defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__) ||\
    defined(__AVR_ATmega168__)
# define FLASH__REGISTER                    SPMCSR
# define FLASH__SELF_PROGRAMMING_ENABLE_BIT SELFPRGEN
#elif defined(__AVR_ATmega8__) || defined(__AVR_ATmega16__)
# define FLASH__REGISTER                    SPMCR
# define FLASH__SELF_PROGRAMMING_ENABLE_BIT SPMEN
#endif


inline static void flash__enable_programming(void) {
    FLASH__REGISTER |= (1<<FLASH__SELF_PROGRAMMING_ENABLE_BIT);
}

#else

#   error "Unsupported MCU"

#endif

#endif