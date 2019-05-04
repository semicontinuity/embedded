// =============================================================================
// EEPROM driver
// procedures are inlineable, so it is easier to place them
// at the desired address during linking (hard with avr-libc)
// =============================================================================

#ifndef __CPU_AVR_EEPROM_H
#define __CPU_AVR_EEPROM_H

#include <stdbool.h>
#include <avr/io.h>


#if defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__) ||\
    defined(__AVR_ATmega168__) ||\
    defined(__AVR_ATmega8__) || defined(__AVR_ATmega16__)


#if defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__) ||\
    defined(__AVR_ATmega168__)
# define EEPROM__MASTER_WRITE_ENABLE_BIT EEMPE
# define EEPROM__WRITE_ENABLE_BIT EEPE
#elif defined(__AVR_ATmega8__) || defined(__AVR_ATmega16__)
# define EEPROM__MASTER_WRITE_ENABLE_BIT EEMWE
# define EEPROM__WRITE_ENABLE_BIT EEWE
#endif


inline static void eeprom__write(void) {
    /* Master write enable */
    EECR |= (1 << EEPROM__MASTER_WRITE_ENABLE_BIT);
    /* Start eeprom write by setting write enable */
    EECR |= (1 << EEPROM__WRITE_ENABLE_BIT);
}

inline static bool eeprom__is_writing(void) {
    return EECR & (1 << EEPROM__WRITE_ENABLE_BIT);
}

inline static unsigned char eeprom__read_byte_unchecked(unsigned char *address) {
    /* Set up address register */
    EEARH = ((int)address >> 8);
    EEARL = ((int)address & 0xFF);
    /* Start eeprom read*/
    EECR |= (1 << EERE);
    /* Return data from Data Register */
    return EEDR;
}

inline static unsigned char eeprom__read_byte(unsigned char *address) {
    /* Wait for completion of previous write */
    while (eeprom__is_writing());
    return eeprom__read_byte_unchecked(address);
}


inline static void eeprom__write_byte(unsigned char *address, unsigned char data) {
    /* Wait for completion of previous write */
    while(eeprom__is_writing());
    /* Set up address and Data Registers */
    EEARH = ((int)address >> 8);
    EEARL = ((int)address & 0xFF);
    EEDR = data;
    eeprom__write();
}


#else

#   error "Unsupported MCU"

#endif

#endif