// =============================================================================
// Bootloader driver
// =============================================================================

#ifndef __CPU_AVR_BOOTLOADER_H
#define __CPU_AVR_BOOTLOADER_H

#include <stdbool.h>
#include <avr/io.h>


#if defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__) ||\
    defined(__AVR_ATmega168__) ||\
    defined(__AVR_ATmega8__) || defined(__AVR_ATmega16__)


#if defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__) ||\
    defined(__AVR_ATmega168__)
# define BOOTLOADER__REGISTER MCUCR
#elif defined(__AVR_ATmega8__) || defined(__AVR_ATmega16__)
# define BOOTLOADER__REGISTER GICR
#endif


inline static void bootloader__set_place_int_vectors_at_beginning(bool value) {
    BOOTLOADER__REGISTER |= 1;   // Enable change of interrupt vectors: set IVCE
    if (value)
        BOOTLOADER__REGISTER |= 2;   // Move interrupts to bootloader: set IVSEL
    else
        BOOTLOADER__REGISTER &= ~2;  // Move interrupts to flash start: clear IVSEL
}

inline static bool bootloader__is_place_int_vectors_at_beginning(void) {
    return BOOTLOADER__REGISTER & 2;
}

#else

#   error "Unsupported MCU"

#endif

#endif