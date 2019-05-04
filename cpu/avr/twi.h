// =============================================================================
// Two-wire interface driver
// =============================================================================

#ifndef __CPU_AVR_TWI_H
#define __CPU_AVR_TWI_H

#include <stdbool.h>
#include <avr/io.h>


#if defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__) ||\
    defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__)

// Currently, only prescaler 1 is supported for simplicity
// NB: WBR should be 10 or higher if the TWI operates in master mode
#define TWI__DIVISOR(/*prescaler,*/rate) ((F_CPU/(rate) - 16)/2/*/(prescaler)*/)

#define TWI__DIVISOR__REGISTER                  TWBR
#define TWI__CONTROL__REGISTER                  TWCR
#define TWI__STATUS__REGISTER                   TWSR
#define TWI__DATA__REGISTER                     TWDR
#define TWI__SLAVE_ADDRESS__REGISTER            TWAR
#define TWI__SLAVE_ADDRESS_MASK__REGISTER       TWAMR

#define TWI__INTERRUPT__HOST                    TWI__CONTROL__REGISTER
#define TWI__INTERRUPT__BIT                     TWINT
#define TWI__ACKNOWLEDGE__HOST                  TWI__CONTROL__REGISTER
#define TWI__ACKNOWLEDGE__BIT                   TWEA
#define TWI__START_CONDITION__HOST              TWI__CONTROL__REGISTER
#define TWI__START_CONDITION__BIT               TWSTA
#define TWI__STOP_CONDITION__HOST               TWI__CONTROL__REGISTER
#define TWI__STOP_CONDITION__BIT                TWSTO
#define TWI__WRITE_COLLISION__HOST              TWI__CONTROL__REGISTER
#define TWI__WRITE_COLLISION__BIT               TWWC
#define TWI__ENABLED__HOST                      TWI__CONTROL__REGISTER
#define TWI__ENABLED__BIT                       TWEN
#define TWI__INTERRUPT__ENABLED__HOST           TWI__CONTROL__REGISTER
#define TWI__INTERRUPT__ENABLED__BIT            TWIE

#define TWI__SLAVE_ADDRESS__BIT_OFFSET          TWA0

#define TWI__STATUS__BUS_ERROR                                                  (0x00)
#define TWI__STATUS__INVALID                                                    (0xF8)

#define TWI__STATUS__SLAVE_WRITE_ACKNOWLEDGED                                   (0x60)
#define TWI__STATUS__SLAVE_WRITE_ACKNOWLEDGED_AFTER_MASTER_ARBITRATION_LOST     (0x68)
#define TWI__STATUS__GENERAL_CALL_ACKNOWLEDGED                                  (0x70)
#define TWI__STATUS__GENERAL_CALL_ACKNOWLEDGED_AFTER_MASTER_ARBITRATION_LOST    (0x78)
#define TWI__STATUS__SLAVE_RECEIVED_DATA_BYTE_ACKNOWLEDGED                      (0x80)
#define TWI__STATUS__SLAVE_RECEIVED_DATA_BYTE_NOT_ACKNOWLEDGED                  (0x88)
#define TWI__STATUS__GENERAL_CALL_DATA_BYTE_ACKNOWLEDGED                        (0x90)
#define TWI__STATUS__GENERAL_CALL_DATA_BYTE_NOT_ACKNOWLEDGED                    (0x98)
#define TWI__STATUS__SLAVE_STOP_OR_REPEATED_START                               (0xA0)

#define TWI__STATUS__SLAVE_READ_ACKNOWLEDGED                                    (0xA8)
#define TWI__STATUS__SLAVE_READ_ACKNOWLEDGED_AFTER_MASTER_ARBITRATION_LOST      (0xB0)
#define TWI__STATUS__SLAVE_TRANSMITTED_DATA_BYTE_ACKNOWLEDGED                   (0xB8)
#define TWI__STATUS__SLAVE_TRANSMITTED_DATA_BYTE_NOT_ACKNOWLEDGED               (0xC0)
#define TWI__STATUS__SLAVE_TRANSMITTED_LAST_DATA_BYTE_ACKNOWLEDGED              (0xC8)


inline static void twi__slave__start(const bool interrupt) {
    if (interrupt) {
        TWI__CONTROL__REGISTER = _BV(TWI__ENABLED__BIT) | _BV(TWI__ACKNOWLEDGE__BIT) | _BV(TWI__INTERRUPT__ENABLED__BIT) | _BV(TWI__INTERRUPT__BIT);
    } else {
        TWI__CONTROL__REGISTER = _BV(TWI__ENABLED__BIT) | _BV(TWI__ACKNOWLEDGE__BIT) | _BV(TWI__INTERRUPT__BIT);
    }
}

inline static void twi__enable(void) {
    TWI__ENABLED__HOST |= (1 << TWI__ENABLED__BIT);
}

inline static void twi__disable(void) {
    TWI__ENABLED__HOST &= ~(1 << TWI__ENABLED__BIT);
}

inline static void twi__enabled__set(const uint8_t enabled) {
    if (enabled) twi__enable(); else twi__disable();
}

/** For master mode */
inline static void twi__divisor__set(const uint8_t divisor) {
    TWI__DIVISOR__REGISTER = divisor;
}

/** For master mode */
inline static void twi__bit_rate__set(const uint32_t bit_rate) {
    twi__divisor__set((uint8_t) TWI__DIVISOR(bit_rate));
}

/** General call unsupported, for simplicity */
inline static void twi__slave_address__set(const uint8_t address) {
    TWI__SLAVE_ADDRESS__REGISTER = address << TWI__SLAVE_ADDRESS__BIT_OFFSET;
}

/** prescaler bits are not masked, for simplicity, because prescaler is 1 */
inline static uint8_t twi__status__get(void) {
    return TWI__STATUS__REGISTER;
}


inline static uint8_t twi__data__get(void) {
    return TWI__DATA__REGISTER;
}

inline static void twi__data__set(const uint8_t value) {
    TWI__DATA__REGISTER = value;
}


inline static bool twi__interrupt__get(void) {
    return (bool) bit_is_set(TWI__INTERRUPT__HOST, TWI__INTERRUPT__BIT);
}

inline static bool twi__is_software_action_required(void) {
    return twi__interrupt__get();
}

/**
 * Instructs TWI unit to continue (by writing 1 to TWI__INTERRUPT__BIT).
 * @param proceed acknowledge (or expect acknowledgement) of the next data byte; respond to slave address
 */
inline static void twi__continue(const bool proceed, const bool transmit_start_when_bus_free) {
    if (transmit_start_when_bus_free) {
        if (proceed) {
            TWI__CONTROL__REGISTER = _BV(TWI__ENABLED__BIT) | _BV(TWI__START_CONDITION__BIT) | _BV(TWI__ACKNOWLEDGE__BIT) | _BV(TWI__INTERRUPT__BIT);
        } else {
            TWI__CONTROL__REGISTER = _BV(TWI__ENABLED__BIT) | _BV(TWI__START_CONDITION__BIT) | _BV(TWI__INTERRUPT__BIT);
        }
    } else {
        if (proceed) {
            TWI__CONTROL__REGISTER = _BV(TWI__ENABLED__BIT) | _BV(TWI__ACKNOWLEDGE__BIT) | _BV(TWI__INTERRUPT__BIT);
        } else {
            TWI__CONTROL__REGISTER = _BV(TWI__ENABLED__BIT) | _BV(TWI__INTERRUPT__BIT);
        }
    }
}


/**
 * Instructs TWI unit to recover form bus error, as described in data sheet.
 * @param acknowledge described as "does not matter", but can be specified.
 */
inline static void twi__recover_from_bus_error(const bool acknowledge) {
    if (acknowledge) {
        TWI__CONTROL__REGISTER = _BV(TWI__ENABLED__BIT) | _BV(TWI__ACKNOWLEDGE__BIT) | _BV(TWI__STOP_CONDITION__BIT) | _BV(TWI__INTERRUPT__BIT);
    } else {
        TWI__CONTROL__REGISTER = _BV(TWI__ENABLED__BIT) | _BV(TWI__STOP_CONDITION__BIT) | _BV(TWI__INTERRUPT__BIT);
    }
}


#else

#   error "Unsupported MCU"

#endif

#endif