// =============================================================================
// EEPROM driver
// procedures are inlineable, so it is easier to place them
// at the desired address during linking (hard with avr-libc)
// =============================================================================

#ifndef __CPU_AVR_EEPROM_H
#define __CPU_AVR_EEPROM_H

#include <avr/io.h>


#if defined(__AVR_ATmega48__)

inline static unsigned char eeprom__read_byte(unsigned char *address) {
    /* Wait for completion of previous write */
    while(EECR & (1<<EEPE));
    /* Set up address register */
    EEARH = 0;
    EEARL = ((int)address & 0xFF);
    /* Start eeprom read*/
    EECR |= (1<<EERE);
    /* Return data from Data Register */
    return EEDR;
}


inline static void eeprom__write_byte(unsigned char *address, unsigned char data) {
    /* Wait for completion of previous write */
    while(EECR & (1<<EEPE));
    /* Set up address and Data Registers */
    EEARH = 0;
    EEARL = ((int)address & 0xFF);
    EEDR = data;
    /* Write logical one to EEMPE */
    EECR |= (1<<EEMPE);
    /* Start eeprom write by setting EEPE */
    EECR |= (1<<EEPE);
}


#else

#   error "Unsupported MCU"

#endif

#endif