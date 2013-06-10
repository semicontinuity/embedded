// =============================================================================
// USART0
//
// API:
//
// usart0__rate__set:
//   Sets the USART bit rate
//
// usart_init:
//   Initialize the USART to typical mode: Async, 8 bit, no parity, 1 stop bit.
//
// usart_out__write:
//   Blocking write
//
// The 32-bit value, made by concatenation of UCSR0x registers,
// is referred to as "configuration value" of the USART.
// To get the particular configuration value,
// combine the appropriate with USART0_CONF_* constants with logical OR.
//
// USART configurations can be switched with usart0__switch_conf() function.
// It produces optimal code, if configuration values are compile-time constants.
// =============================================================================

#ifndef __CPU__AVR__USART0_H
#define __CPU__AVR__USART0_H

#include <stdint.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "cpu/avr/gpio.h"



#if defined(__AVR_ATmega48__)\
 || defined(__AVR_ATmega88__)\
 || defined(__AVR_ATmega168__)\
 || defined(__AVR_ATmega328__)\
 || defined(__AVR_ATmega48P__)\
 || defined(__AVR_ATmega88P__)\
 || defined(__AVR_ATmega168P__)\
 || defined(__AVR_ATmega328P__)

#define USART0_CONF_REGA(v)             (((v) & 0xFF) << 0)
#define USART0_CONF_REGB(v)             (((v) & 0xFF) << 8)
#define USART0_CONF_REGC(v)             (((v) & 0xFF) << 16)
#define USART0_CONF_REGD(v)             (((v) & 0xFF) << 24)


#define USART0_CONF_DOUBLE_SPEED        USART0_CONF_REGA(1<<U2X0)

#define USART0_CONF_MULTIPROCESSOR      USART0_CONF_REGA(1<<MPCM0)

#define USART0_CONF_RX_COMPLETE_INT     USART0_CONF_REGB(1<<RXCIE0)
#define USART0_CONF_TX_COMPLETE_INT     USART0_CONF_REGB(1<<TXCIE0)
#define USART0_CONF_DATA_REG_EMPTY_INT  USART0_CONF_REGB(1<<UDRIE0)
#define USART0_CONF_RX_ENABLED          USART0_CONF_REGB(1<<RXEN0)
#define USART0_CONF_TX_ENABLED          USART0_CONF_REGB(1<<TXEN0)

#define USART0_CONF_MODE_ASYNC       	USART0_CONF_REGC((0<<UMSEL01)|(0<<UMSEL00))
#define USART0_CONF_MODE_SYNC           USART0_CONF_REGC((0<<UMSEL01)|(1<<UMSEL00))
#define USART0_CONF_MODE_RESERVED       USART0_CONF_REGC((1<<UMSEL01)|(0<<UMSEL00))
#define USART0_CONF_MODE_SPI_MASTER     USART0_CONF_REGC((1<<UMSEL01)|(1<<UMSEL00))

#define USART0_CONF_PARITY_DISABLED     USART0_CONF_REGC((0<<UPM01)|(0<<UPM00))
#define USART0_CONF_PARITY_RESERVED     USART0_CONF_REGC((0<<UPM01)|(1<<UPM00))
#define USART0_CONF_PARITY_EVEN         USART0_CONF_REGC((1<<UPM01)|(0<<UPM00))
#define USART0_CONF_PARITY_ODD          USART0_CONF_REGC((1<<UPM01)|(1<<UPM00))

#define USART0_CONF_STOP_BITS_1         USART0_CONF_REGC(0<<USBS0)
#define USART0_CONF_STOP_BITS_2         USART0_CONF_REGC(1<<USBS0)

#define USART0_CONF_CHAR_SIZE_5_BIT     (USART0_CONF_REGB(0<<UCSZ02) | USART0_CONF_REGC((0<<UCSZ01)|(0<<UCSZ00)))
#define USART0_CONF_CHAR_SIZE_6_BIT     (USART0_CONF_REGB(0<<UCSZ02) | USART0_CONF_REGC((0<<UCSZ01)|(1<<UCSZ00)))
#define USART0_CONF_CHAR_SIZE_7_BIT     (USART0_CONF_REGB(0<<UCSZ02) | USART0_CONF_REGC((1<<UCSZ01)|(0<<UCSZ00)))
#define USART0_CONF_CHAR_SIZE_8_BIT     (USART0_CONF_REGB(0<<UCSZ02) | USART0_CONF_REGC((1<<UCSZ01)|(1<<UCSZ00)))
#define USART0_CONF_CHAR_SIZE_RESERVED4 (USART0_CONF_REGB(1<<UCSZ02) | USART0_CONF_REGC((0<<UCSZ01)|(0<<UCSZ00)))
#define USART0_CONF_CHAR_SIZE_RESERVED5 (USART0_CONF_REGB(1<<UCSZ02) | USART0_CONF_REGC((0<<UCSZ01)|(1<<UCSZ00)))
#define USART0_CONF_CHAR_SIZE_RESERVED6 (USART0_CONF_REGB(1<<UCSZ02) | USART0_CONF_REGC((1<<UCSZ01)|(0<<UCSZ00)))
#define USART0_CONF_CHAR_SIZE_9_BIT     (USART0_CONF_REGB(1<<UCSZ02) | USART0_CONF_REGC((1<<UCSZ01)|(1<<UCSZ00)))

#define USART0_CONF_POLARITY_0          (USART0_CONF_REGC(0<<UCPOL0)
#define USART0_CONF_POLARITY_1          (USART0_CONF_REGC(1<<UCPOL0))

#define USART0_CONF_DEFAULT             (USART0_CONF_CHAR_SIZE_8_BIT)


inline void usart0__switch_conf(const uint32_t old_conf, const uint32_t new_conf) {
    const uint8_t old_rega = old_conf & 0xFF;
    const uint8_t new_rega = new_conf & 0xFF;
    if (old_rega != new_rega) UCSR0A = new_rega;

    const uint8_t old_regb = (old_conf >> 8) & 0xFF;
    const uint8_t new_regb = (new_conf >> 8) & 0xFF;
    if (old_regb != new_regb) UCSR0B = new_regb;

    const uint8_t old_regc = (old_conf >> 16) & 0xFF;
    const uint8_t new_regc = (new_conf >> 16) & 0xFF;
    if (old_regc != new_regc) UCSR0C = new_regc;
}
#elif defined(__AVR_ATmega16__) || defined(__AVR_ATmega8__)
    // usart0__switch_conf not supported yet
#else
    #error "Unsupported MCU"
#endif



#if defined(__AVR_ATmega48__)\
 || defined(__AVR_ATmega88__)\
 || defined(__AVR_ATmega168__)\
 || defined(__AVR_ATmega328__)\
 || defined(__AVR_ATmega48P__)\
 || defined(__AVR_ATmega88P__)\
 || defined(__AVR_ATmega168P__)\
 || defined(__AVR_ATmega328P__)

#define usart0__rx__complete_interrupt__VECTOR                    (USART_RX_vect)

#define usart0__rx__complete_interrupt__enabled__HOST             (UCSR0B)
#define usart0__rx__complete_interrupt__enabled__BIT              (RXCIE0)

#define usart0__tx__data_register_empty_interrupt__enabled__HOST  (UCSR0B)
#define usart0__tx__data_register_empty_interrupt__enabled__BIT   (UDRIE0)


#elif defined(__AVR_ATmega16__)


#define usart0__rx__complete_interrupt__VECTOR                    (USART_RXC_vect)
#define usart0__tx__data_register_empty_interrupt__VECTOR         (USART_UDRE_vect)

#define usart0__rx__complete_interrupt__enabled__HOST             (UCSRB)
#define usart0__rx__complete_interrupt__enabled__BIT              (RXCIE)

#define usart0__tx__data_register_empty_interrupt__enabled__HOST  (UCSRB)
#define usart0__tx__data_register_empty_interrupt__enabled__BIT   (UDRIE)

#endif


// =============================================================================
// usart0__rate__set
// =============================================================================
inline uint16_t UBRR_VALUE(uint32_t rate) {
    return (uint16_t)((F_CPU/8/(rate) - 1)/2);
}


#if defined(__AVR_ATmega48__)\
 || defined(__AVR_ATmega88__)\
 || defined(__AVR_ATmega168__)\
 || defined(__AVR_ATmega328__)\
 || defined(__AVR_ATmega48P__)\
 || defined(__AVR_ATmega88P__)\
 || defined(__AVR_ATmega168P__)\
 || defined(__AVR_ATmega328P__)

inline void usart0__divisor__set(const uint16_t divisor) {
    UBRR0H = (uint8_t)(divisor>>8);
    UBRR0L = (uint8_t)(divisor);
}

inline void usart0__rate__set(const uint32_t rate) {
    UBRR0H = (uint8_t)(UBRR_VALUE(rate)>>8);
    UBRR0L = (uint8_t)(UBRR_VALUE(rate));
}

#elif defined(__AVR_ATmega8__) || defined(__AVR_ATmega16__)

inline void usart0__divisor__set(const uint16_t divisor) {
    UBRRH = (uint8_t)(divisor>>8);
    UBRRL = (uint8_t)(divisor);
}

inline void usart0__rate__set(const uint32_t rate) {
    UBRRH = (uint8_t)(UBRR_VALUE(rate)>>8);
    UBRRL = (uint8_t)(UBRR_VALUE(rate));
}

#elif defined(__AVR_AT90S2313__)

inline void usart0__divisor__set(const uint16_t divisor) {
    UBRR = (uint8_t)(divisor);
}

inline void usart0__rate__set(uint32_t rate) {
    UBRR=(uint8_t)(UBRR_VALUE(rate));
}

#else
    #error "Unsupported MCU"
#endif


// =============================================================================
// usart_init
// =============================================================================

inline void usart0__init(void) {
//           Asynch UART               No parity             1 stopbit  8 bit(+reg B)   polarity
#if defined(__AVR_ATmega48__)\
 || defined(__AVR_ATmega88__)\
 || defined(__AVR_ATmega168__)\
 || defined(__AVR_ATmega328__)\
 || defined(__AVR_ATmega48P__)\
 || defined(__AVR_ATmega88P__)\
 || defined(__AVR_ATmega168P__)\
 || defined(__AVR_ATmega328P__)
//  UMSEL=00	Asynch UART
//  UPM=00	No Parity
//  USBS=0	1 stop bit
//  UCSZ=011	8 bit
//  UCPOL0=0	Polarity: Rising, 0 for Asynch.
    UCSR0C = (0<<UMSEL01)|(0<<UMSEL00)|(0<<UPM01)|(0<<UPM00)|(0<<USBS0)|(3<<UCSZ00)|(0<<UCPOL0);
#elif defined(__AVR_ATmega8__) || defined(__AVR_ATmega16__)
    UCSRC = (1<<URSEL)|(0<<UMSEL)|(0<<UPM1)|(0<<UPM0)|(0<<USBS)|(3<<UCSZ0)|(0<<UCPOL);
#else
    #error "Unsupported MCU"
#endif
}


// =============================================================================
// usart0__in__enabled__set
// =============================================================================

inline void usart0__in__enabled__set(void) {
#if defined(__AVR_ATmega48__)\
 || defined(__AVR_ATmega88__)\
 || defined(__AVR_ATmega168__)\
 || defined(__AVR_ATmega328__)\
 || defined(__AVR_ATmega48P__)\
 || defined(__AVR_ATmega88P__)\
 || defined(__AVR_ATmega168P__)\
 || defined(__AVR_ATmega328P__)
    set_bit_in_reg(UCSR0B, RXEN0);
#elif defined(__AVR_ATmega8__) || defined(__AVR_ATmega16__)
    set_bit_in_reg(UCSRB, RXEN);
#else
    #error "Unsupported MCU"
#endif
}


// =============================================================================
// usart0__in__peek
// =============================================================================

inline char usart0__in__peek(void) {
#if defined(__AVR_ATmega48__)\
 || defined(__AVR_ATmega88__)\
 || defined(__AVR_ATmega168__)\
 || defined(__AVR_ATmega328__)\
 || defined(__AVR_ATmega48P__)\
 || defined(__AVR_ATmega88P__)\
 || defined(__AVR_ATmega168P__)\
 || defined(__AVR_ATmega328P__)
    return UDR0;
#elif defined(__AVR_ATmega8__) || defined(__AVR_ATmega16__)
    return UDR;
#else
    #error "Unsupported MCU"
#endif
}


// =============================================================================
// usart0__in__complete_interrupt_enabled__set
// =============================================================================

inline void usart0__in__complete_interrupt_enabled__set(void) {
#if defined(__AVR_ATmega48__)\
 || defined(__AVR_ATmega88__)\
 || defined(__AVR_ATmega168__)\
 || defined(__AVR_ATmega328__)\
 || defined(__AVR_ATmega48P__)\
 || defined(__AVR_ATmega88P__)\
 || defined(__AVR_ATmega168P__)\
 || defined(__AVR_ATmega328P__)
    set_bit_in_reg(UCSR0B, RXCIE0);
#elif defined(__AVR_ATmega8__) || defined(__AVR_ATmega16__)
    set_bit_in_reg(UCSRB, RXCIE);
#else
    #error "Unsupported MCU"
#endif
}


// =============================================================================
// usart0__out__enabled__set
// =============================================================================

inline void usart0__out__enabled__set(void) {
#if defined(__AVR_ATmega48__)\
 || defined(__AVR_ATmega88__)\
 || defined(__AVR_ATmega168__)\
 || defined(__AVR_ATmega328__)\
 || defined(__AVR_ATmega48P__)\
 || defined(__AVR_ATmega88P__)\
 || defined(__AVR_ATmega168P__)\
 || defined(__AVR_ATmega328P__)
    set_bit_in_reg(UCSR0B, TXEN0);
#elif defined(__AVR_ATmega8__) || defined(__AVR_ATmega16__)
    set_bit_in_reg(UCSRB, TXEN);
#else
    #error "Unsupported MCU"
#endif
}


#endif