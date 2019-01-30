// =============================================================================
// Two-wire interface driver
// =============================================================================

#ifndef __CPU_AVR_TWI_H
#define __CPU_AVR_TWI_H

#include <stdbool.h>
#include <avr/io.h>


#if defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__) ||\
    defined(__AVR_ATmega168__)


# define TWI__BIT_RATE__REGISTER            TWBR
# define TWI__CONTROL__REGISTER             TWCR
# define TWI__STATUS__REGISTER              TWSR
# define TWI__DATA__REGISTER                TWDR
# define TWI__SLAVE_ADDRESS__REGISTER       TWAR
# define TWI__SLAVE_ADDRESS_MASK__REGISTER  TWAMR

# define TWI__INTERRUPT__HOST               TWI__CONTROL__REGISTER
# define TWI__INTERRUPT__BIT                TWINT

# define TWI__ACKNOWLEDGE__HOST             TWI__CONTROL__REGISTER
# define TWI__ACKNOWLEDGE__BIT              TWEA

# define TWI__START_CONDITION__HOST         TWI__CONTROL__REGISTER
# define TWI__START_CONDITION__BIT          TWSTA

# define TWI__STOP_CONDITION__HOST          TWI__CONTROL__REGISTER
# define TWI__STOP_CONDITION__BIT           TWSTO

# define TWI__WRITE_COLLISION__HOST         TWI__CONTROL__REGISTER
# define TWI__WRITE_COLLISION__BIT          TWWC

# define TWI__ENABLED__HOST                 TWI__CONTROL__REGISTER
# define TWI__ENABLED__BIT                  TWEN

# define TWI__INTERRUPT__ENABLED__HOST      TWI__CONTROL__REGISTER
# define TWI__INTERRUPT__ENABLED__BIT       TWIEN


inline static void twi__enable(void) {
    TWI__ENABLED__HOST |= (1 << TWI__ENABLED__BIT);
}

inline static void twi__disable(void) {
    TWI__ENABLED__HOST &= ~(1 << TWI__ENABLED__BIT);
}

inline static void twi__enabled__set(const uint8_t enabled) {
    if (enabled) twi__enable(); else twi__disable();
}

#else

#   error "Unsupported MCU"

#endif

#endif