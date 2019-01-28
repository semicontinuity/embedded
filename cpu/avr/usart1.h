// =============================================================================
// USART1
//
// API:
//
// usart1__rate__set:
//   Sets the USART bit rate
//
// usart1__init:
//   Initialize the USART to typical mode: Async, 8 bit, no parity, 1 stop bit.
//
// usart1__out__write:
//   Blocking write
//
// The 32-bit value, made by concatenation of UCSR1x registers,
// is referred to as "configuration value" of the USART.
// To get the particular configuration value,
// combine the appropriate with USART1_CONF_* constants with logical OR.
//
// USART configurations can be switched with usart1__switch_conf() function.
// It produces optimal code, if configuration values are compile-time constants.
// =============================================================================

#ifndef __CPU__AVR__USART1_H
#define __CPU__AVR__USART1_H

#include <stdint.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "cpu/avr/gpio.h"



#if defined(__AVR_AT90USB82__) || defined(__AVR_AT90USB162__)

#define USART1_CONF_REGA(v)             ((((uint32_t)v) & 0xFF) << 0)
#define USART1_CONF_REGB(v)             ((((uint32_t)v) & 0xFF) << 8)
#define USART1_CONF_REGC(v)             ((((uint32_t)v) & 0xFF) << 16)
#define USART1_CONF_REGD(v)             ((((uint32_t)v) & 0xFF) << 24)


#define USART1_CONF_DOUBLE_SPEED        USART1_CONF_REGA(1<<U2X1)

#define USART1_CONF_MULTIPROCESSOR      USART1_CONF_REGA(1<<MPCM1)

#define USART1_CONF_RX_COMPLETE_INT     USART1_CONF_REGB(1<<RXCIE1)
#define USART1_CONF_TX_COMPLETE_INT     USART1_CONF_REGB(1<<TXCIE1)
#define USART1_CONF_DATA_REG_EMPTY_INT  USART1_CONF_REGB(1<<UDRIE1)
#define USART1_CONF_RX_ENABLED          USART1_CONF_REGB(1<<RXEN1)
#define USART1_CONF_TX_ENABLED          USART1_CONF_REGB(1<<TXEN1)

#define USART1_CONF_MODE_ASYNC       	USART1_CONF_REGC((0<<UMSEL11)|(0<<UMSEL10))
#define USART1_CONF_MODE_SYNC           USART1_CONF_REGC((0<<UMSEL11)|(1<<UMSEL10))
#define USART1_CONF_MODE_RESERVED       USART1_CONF_REGC((1<<UMSEL11)|(0<<UMSEL10))
#define USART1_CONF_MODE_SPI_MASTER     USART1_CONF_REGC((1<<UMSEL11)|(1<<UMSEL10))

#define USART1_CONF_PARITY_DISABLED     USART1_CONF_REGC((0<<UPM11)|(0<<UPM10))
#define USART1_CONF_PARITY_RESERVED     USART1_CONF_REGC((0<<UPM11)|(1<<UPM10))
#define USART1_CONF_PARITY_EVEN         USART1_CONF_REGC((1<<UPM11)|(0<<UPM10))
#define USART1_CONF_PARITY_ODD          USART1_CONF_REGC((1<<UPM11)|(1<<UPM10))

#define USART1_CONF_STOP_BITS_1         USART1_CONF_REGC(0<<USBS1)
#define USART1_CONF_STOP_BITS_2         USART1_CONF_REGC(1<<USBS1)

#define USART1_CONF_CHAR_SIZE_5_BIT     (USART1_CONF_REGB(0<<UCSZ12) | USART1_CONF_REGC((0<<UCSZ11)|(0<<UCSZ10)))
#define USART1_CONF_CHAR_SIZE_6_BIT     (USART1_CONF_REGB(0<<UCSZ12) | USART1_CONF_REGC((0<<UCSZ11)|(1<<UCSZ10)))
#define USART1_CONF_CHAR_SIZE_7_BIT     (USART1_CONF_REGB(0<<UCSZ12) | USART1_CONF_REGC((1<<UCSZ11)|(0<<UCSZ10)))
#define USART1_CONF_CHAR_SIZE_8_BIT     (USART1_CONF_REGB(0<<UCSZ12) | USART1_CONF_REGC((1<<UCSZ11)|(1<<UCSZ10)))
#define USART1_CONF_CHAR_SIZE_RESERVED4 (USART1_CONF_REGB(1<<UCSZ12) | USART1_CONF_REGC((0<<UCSZ11)|(0<<UCSZ10)))
#define USART1_CONF_CHAR_SIZE_RESERVED5 (USART1_CONF_REGB(1<<UCSZ12) | USART1_CONF_REGC((0<<UCSZ11)|(1<<UCSZ10)))
#define USART1_CONF_CHAR_SIZE_RESERVED6 (USART1_CONF_REGB(1<<UCSZ12) | USART1_CONF_REGC((1<<UCSZ11)|(0<<UCSZ10)))
#define USART1_CONF_CHAR_SIZE_9_BIT     (USART1_CONF_REGB(1<<UCSZ12) | USART1_CONF_REGC((1<<UCSZ11)|(1<<UCSZ10)))

#define USART1_CONF_POLARITY_0          (USART1_CONF_REGC(0<<UCPOL1)
#define USART1_CONF_POLARITY_1          (USART1_CONF_REGC(1<<UCPOL1))

#define USART1_CONF_RTS_ENABLED         (USART1_CONF_REGD(1<<RTSEN))
#define USART1_CONF_CTS_ENABLED         (USART1_CONF_REGD(1<<CTSEN))

#define USART1_CONF_DEFAULT             (USART1_CONF_CHAR_SIZE_8_BIT)


inline void usart1__switch_conf(const uint32_t old_conf, const uint32_t new_conf) {
    const uint8_t old_rega = old_conf & 0xFF;
    const uint8_t new_rega = new_conf & 0xFF;
    if (old_rega != new_rega) UCSR1A = new_rega;

    const uint8_t old_regb = (old_conf >> 8) & 0xFF;
    const uint8_t new_regb = (new_conf >> 8) & 0xFF;
    if (old_regb != new_regb) UCSR1B = new_regb;

    const uint8_t old_regc = (old_conf >> 16) & 0xFF;
    const uint8_t new_regc = (new_conf >> 16) & 0xFF;
    if (old_regc != new_regc) UCSR1C = new_regc;

    const uint8_t old_regd = (old_conf >> 24) & 0xFF;
    const uint8_t new_regd = (new_conf >> 24) & 0xFF;
    if (old_regd != new_regd) UCSR1D = new_regd;
}

#else
    #error "Unsupported MCU"
#endif


#if defined(__AVR_AT90USB82__) || defined(__AVR_AT90USB162__)

#define usart1__rx__complete_interrupt__VECTOR                    (USART_RX_vect)

#define usart1__rx__complete_interrupt__enabled__HOST             (UCSR1B)
#define usart1__rx__complete_interrupt__enabled__BIT              (RXCIE1)

#define usart1__tx__data_register_empty_interrupt__enabled__HOST  (UCSR1B)
#define usart1__tx__data_register_empty_interrupt__enabled__BIT   (UDRIE1)

#endif


// =============================================================================
// usart1__rate__set
// =============================================================================
inline uint16_t UBRR_VALUE(uint32_t rate) {
    return (uint16_t)((F_CPU/8/(rate) - 1)/2);
}

#if defined(__AVR_AT90USB82__) || defined(__AVR_AT90USB162__)

inline void usart1__divisor__set(const uint16_t divisor) {
    UBRR1H = (uint8_t)(divisor>>8);
    UBRR1L = (uint8_t)(divisor);
}

inline void usart1__rate__set(const uint32_t rate) {
    UBRR1H = (uint8_t)(UBRR_VALUE(rate)>>8);
    UBRR1L = (uint8_t)(UBRR_VALUE(rate));
}

#else
    #error "Unsupported MCU"
#endif


// =============================================================================
// usart1__init
// =============================================================================

inline void usart1__init(void) {
//           Asynch UART               No parity             1 stopbit  8 bit(+reg B)   polarity
#if defined(__AVR_AT90USB82__) || defined(__AVR_AT90USB162__)
//  UMSEL=00	Asynch UART
//  UPM=00	No Parity
//  USBS=0	1 stop bit
//  UCSZ=011	8 bit
//  UCPOL0=0	Polarity: Rising, 0 for Asynch.
    UCSR1C = (0<<UMSEL11)|(0<<UMSEL10)|(0<<UPM11)|(0<<UPM10)|(0<<USBS1)|(3<<UCSZ10)|(0<<UCPOL1);
#else
    #error "Unsupported MCU"
#endif
}


// =============================================================================
// usart1__in__enabled__set
// =============================================================================

inline void usart1__in__enabled__set(void) {
#if defined(__AVR_AT90USB82__) || defined(__AVR_AT90USB162__)
    set_bit_in_reg(UCSR1B, RXEN1);
#else
    #error "Unsupported MCU"
#endif
}


// =============================================================================
// usart1__in__peek
// =============================================================================

inline char usart1__in__peek(void) {
#if defined(__AVR_AT90USB82__) || defined(__AVR_AT90USB162__)
    return UDR1;
#else
    #error "Unsupported MCU"
#endif
}


// =============================================================================
// usart1__in__complete_interrupt__enabled__set
// =============================================================================

inline void usart1__in__complete_interrupt__enabled__set(void) {
#if defined(__AVR_AT90USB82__) || defined(__AVR_AT90USB162__)
    set_bit_in_reg(UCSR1B, RXCIE1);
#else
    #error "Unsupported MCU"
#endif
}


// =============================================================================
// usart1__out__enabled__set
// =============================================================================

inline void usart1__out__enabled__set(void) {
#if defined(__AVR_AT90USB82__) || defined(__AVR_AT90USB162__)
    set_bit_in_reg(UCSR1B, TXEN1);
#else
    #error "Unsupported MCU"
#endif
}


#endif