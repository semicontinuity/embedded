// =============================================================================
// Driver for the first USART (usually USART0, but sometimes USART1)
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
#include "util/bitops.h"


#if defined(__AVR_AT90USB82__)\
 || defined(__AVR_AT90USB162__)

#  define usart0__rx__complete__interrupt__VECTOR                         (USART1_RX_vect)
#  define usart0__tx__complete__interrupt__VECTOR                         (USART1_TX_vect)
#  define usart0__tx__data_register_empty__interrupt__VECTOR              (USART1_UDRE_vect)

#elif defined(__AVR_ATmega48__)\
 || defined(__AVR_ATmega88__)\
 || defined(__AVR_ATmega168__)\
 || defined(__AVR_ATmega328__)\
 || defined(__AVR_ATmega48P__)\
 || defined(__AVR_ATmega88P__)\
 || defined(__AVR_ATmega168P__)\
 || defined(__AVR_ATmega328P__)\
 || defined(__AVR_ATmega8535__)

#  define usart0__rx__complete__interrupt__VECTOR                         (USART_RX_vect)
#  define usart0__tx__complete__interrupt__VECTOR                         (USART_TX_vect)
#  define usart0__tx__data_register_empty__interrupt__VECTOR              (USART_UDRE_vect)

#elif defined(__AVR_ATmega16__)\
 || defined(__AVR_ATmega8__)\
 || defined(__AVR_ATmega32__)

#  define usart0__rx__complete__interrupt__VECTOR                         (USART_RXC_vect)
#  define usart0__tx__complete__interrupt__VECTOR                         (USART_TXC_vect)
#  define usart0__tx__data_register_empty__interrupt__VECTOR              (USART_UDRE_vect)

#elif defined(__AVR_AT90S8535__)\
 || defined(__AVR_AT90S2313__)

#  define usart0__rx__complete__interrupt__VECTOR                         (UART_RX_vect)
#  define usart0__tx__complete__interrupt__VECTOR                         (UART_TX_vect)
#  define usart0__tx__data_register_empty__interrupt__VECTOR              (UART_UDRE_vect)

#else
#  error "Unsupported MCU!"
#endif



#if defined(__AVR_AT90USB82__) || defined(__AVR_AT90USB162__)


#define USART0_REG_A                                                    (UCSR1A)
#define USART0_REG_B                                                    (UCSR1B)
#define USART0_REG_C                                                    (UCSR1C)
#define USART0_REG_D                                                    (UCSR1D)

#define USART0_DATA_REGISTER                                            (UDR1)
#define USART0_BIT_RATE_REGISTER                                        (UBRR1)
#define USART0_BIT_RATE_REGISTER_TYPE                                   uint16_t

#define usart0__rx__enabled__HOST                                       (UCSR1B)
#define usart0__rx__enabled__BIT                                        (RXEN1)
#define usart0__tx__enabled__HOST                                       (UCSR1B)
#define usart0__tx__enabled__BIT                                        (TXEN1)

#define usart0__rx__frame_error__HOST                                   (UCSR1A)
#define usart0__rx__frame_error__BIT                                    (FE1)
#define usart0__rx__data_overrun__HOST                                  (UCSR1A)
#define usart0__rx__data_overrun__BIT                                   (DOR1)
#define usart0__rx__parity_error__HOST                                  (UCSR1A)
#define usart0__rx__parity_error__BIT                                   (UPE1)

#define usart0__rx__complete__value__HOST                               (UCSR1A)
#define usart0__rx__complete__value__BIT                                (RXC1)
#define usart0__rx__complete__interrupt__enabled__HOST                  (UCSR1B)
#define usart0__rx__complete__interrupt__enabled__BIT                   (RXCIE1)

#define usart0__tx__complete__value__HOST                               (UCSR1A)
#define usart0__tx__complete__value__BIT                                (TXC1)
#define usart0__tx__complete__interrupt__enabled__HOST                  (UCSR1B)
#define usart0__tx__complete__interrupt__enabled__BIT                   (TXCIE1)

#define usart0__tx__data_register_empty__value__HOST                    (UCSR1A)
#define usart0__tx__data_register_empty__value__BIT                     (UDRE1)
#define usart0__tx__data_register_empty__interrupt__enabled__HOST       (UCSR1B)
#define usart0__tx__data_register_empty__interrupt__enabled__BIT        (UDRIE1)

#define usart0__double_speed__BIT                                       (U2X1)
#define usart0__multiprocessor__BIT                                     (MPCM1)
#define usart0__polarity__BIT                                           (UCPOL1)
#define usart0__char_size0__BIT                                         (UCSZ10)
#define usart0__char_size2__BIT                                         (UCSZ12)
#define usart0__stop_bits__BIT                                          (USBS1)
#define usart0__mode__BIT                                               (UMSEL10)
#define usart0__parity__BIT                                             (UMPM1)


#elif defined(__AVR_ATmega48__)\
 || defined(__AVR_ATmega88__)\
 || defined(__AVR_ATmega168__)\
 || defined(__AVR_ATmega328__)\
 || defined(__AVR_ATmega48P__)\
 || defined(__AVR_ATmega88P__)\
 || defined(__AVR_ATmega168P__)\
 || defined(__AVR_ATmega328P__)


#define USART0_REG_A                                                    (UCSR0A)
#define USART0_REG_B                                                    (UCSR0B)
#define USART0_REG_C                                                    (UCSR0C)

#define USART0_DATA_REGISTER                                            (UDR0)
#define USART0_BIT_RATE_REGISTER                                        (UBRR0)
#define USART0_BIT_RATE_REGISTER_TYPE                                   uint16_t

#define usart0__rx__enabled__HOST                                       (UCSR0B)
#define usart0__rx__enabled__BIT                                        (RXEN0)
#define usart0__tx__enabled__HOST                                       (UCSR0B)
#define usart0__tx__enabled__BIT                                        (TXEN0)

#define usart0__rx__frame_error__HOST                                   (UCSR0A)
#define usart0__rx__frame_error__BIT                                    (FE0)
#define usart0__rx__data_overrun__HOST                                  (UCSR0A)
#define usart0__rx__data_overrun__BIT                                   (DOR0)
#define usart0__rx__parity_error__HOST                                  (UCSR0A)
#define usart0__rx__parity_error__BIT                                   (UPE0)

#define usart0__rx__complete__value__HOST                               (UCSR0A)
#define usart0__rx__complete__value__BIT                                (RXC0)
#define usart0__rx__complete__interrupt__enabled__HOST                  (UCSR0B)
#define usart0__rx__complete__interrupt__enabled__BIT                   (RXCIE0)

#define usart0__tx__complete__value__HOST                               (UCSR0A)
#define usart0__tx__complete__value__BIT                                (TXC0)
#define usart0__tx__complete__interrupt__enabled__HOST                  (UCSR0B)
#define usart0__tx__complete__interrupt__enabled__BIT                   (TXCIE0)

#define usart0__tx__data_register_empty__value__HOST                    (UCSR0A)
#define usart0__tx__data_register_empty__value__BIT                     (UDRE0)
#define usart0__tx__data_register_empty__interrupt__enabled__HOST       (UCSR0B)
#define usart0__tx__data_register_empty__interrupt__enabled__BIT        (UDRIE0)

#define usart0__double_speed__HOST                                      (UCSR0A)
#define usart0__double_speed__BIT                                       (U2X0)

#define usart0__multiprocessor__BIT                                     (MPCM0)
#define usart0__polarity__BIT                                           (UCPOL0)
#define usart0__char_size0__BIT                                         (UCSZ00)
#define usart0__char_size2__BIT                                         (UCSZ02)
#define usart0__stop_bits__BIT                                          (USBS0)
#define usart0__mode__BIT                                               (UMSEL00)
#define usart0__parity__BIT                                             (UMPM0)


#elif defined(__AVR_ATmega16__) || defined(__AVR_ATmega8__) || defined(__AVR_ATmega8535__) || defined(__AVR_ATmega32__)


#define USART0_REG_A                                                    (UCSRA)
#define USART0_REG_B                                                    (UCSRB)
#define USART0_REG_C                                                    (UCSRC)

#define USART0_DATA_REGISTER                                            (UDR)
#define USART0_BIT_RATE_REGISTER                                        (UBRR)
#define USART0_BIT_RATE_REGISTER_TYPE                                   uint16_t

#define usart0__rx__enabled__HOST                                       (UCSRB)
#define usart0__rx__enabled__BIT                                        (RXEN)
#define usart0__tx__enabled__HOST                                       (UCSRB)
#define usart0__tx__enabled__BIT                                        (TXEN)

#define usart0__rx__frame_error__HOST                                   (UCSRA)
#define usart0__rx__frame_error__BIT                                    (FE)
#define usart0__rx__data_overrun__HOST                                  (UCSRA)
#define usart0__rx__data_overrun__BIT                                   (DOR)
#define usart0__rx__parity_error__HOST                                  (UCSRA)
#define usart0__rx__parity_error__BIT                                   (UPE)

#define usart0__rx__complete__value__HOST                               (UCSRA)
#define usart0__rx__complete__value__BIT                                (RXC)
#define usart0__rx__complete__interrupt__enabled__HOST                  (UCSRB)
#define usart0__rx__complete__interrupt__enabled__BIT                   (RXCIE)

#define usart0__tx__complete__value__HOST                               (UCSRA)
#define usart0__tx__complete__value__BIT                                (TXC)
#define usart0__tx__complete__interrupt__enabled__HOST                  (UCSRB)
#define usart0__tx__complete__interrupt__enabled__BIT                   (TXCIE)

#define usart0__tx__data_register_empty__value__HOST                    (UCSRA)
#define usart0__tx__data_register_empty__value__BIT                     (UDRE)
#define usart0__tx__data_register_empty__interrupt__enabled__HOST       (UCSRB)
#define usart0__tx__data_register_empty__interrupt__enabled__BIT        (UDRIE)

#define usart0__double_speed__BIT                                       (U2X)
#define usart0__multiprocessor__BIT                                     (MPCM)
#define usart0__char_size0__BIT                                         (UCSZ0)
#define usart0__char_size2__BIT                                         (UCSZ2)
#define usart0__stop_bits__BIT                                          (USBS)
#define usart0__mode__BIT                                               (UMSEL0)
#define usart0__parity__BIT                                             (UMPM)



#elif defined(__AVR_AT90S8535__) || defined(__AVR_AT90S2313__)


#define USART0_REG_A                                                    (USR)
#define USART0_REG_B                                                    (UCR)

#define USART0_DATA_REGISTER                                            (UDR)
#define USART0_BIT_RATE_REGISTER                                        (UBRR)
#define USART0_BIT_RATE_REGISTER_TYPE                                   uint8_t

#define usart0__rx__enabled__HOST                                       (UCR)
#define usart0__rx__enabled__BIT                                        (RXEN)
#define usart0__tx__enabled__HOST                                       (UCR)
#define usart0__tx__enabled__BIT                                        (TXEN)

#define usart0__rx__frame_error__HOST                                   (USR)
#define usart0__rx__frame_error__BIT                                    (FE)
#define usart0__rx__data_overrun__HOST                                  (USR)
#define usart0__rx__data_overrun__BIT                                   (OR)

#define usart0__rx__complete__value__HOST                               (USR)
#define usart0__rx__complete__value__BIT                                (RXC)
#define usart0__rx__complete__interrupt__enabled__HOST                  (UCR)
#define usart0__rx__complete__interrupt__enabled__BIT                   (RXCIE)

#define usart0__tx__complete__value__HOST                               (USR)
#define usart0__tx__complete__value__BIT                                (TXC)
#define usart0__tx__complete__interrupt__enabled__HOST                  (UCR)
#define usart0__tx__complete__interrupt__enabled__BIT                   (TXCIE)

#define usart0__tx__data_register_empty__value__HOST                    (USR)
#define usart0__tx__data_register_empty__value__BIT                     (UDRE)
#define usart0__tx__data_register_empty__interrupt__enabled__HOST       (UCR)
#define usart0__tx__data_register_empty__interrupt__enabled__BIT        (UDRIE)


#else
#error "Unsupported MCU!"
#endif



#define USART0_CONF_BYTE_A(v)                                           (((v) & 0xFF) << 0)
#define USART0_CONF_BYTE_B(v)                                           (((v) & 0xFF) << 8)
#define USART0_CONF_BYTE_C(v)                                           (((v) & 0xFF) << 16)
#define USART0_CONF_BYTE_D(v)                                           (((v) & 0xFF) << 24)


inline void usart0__switch_conf(const uint32_t old_conf, const uint32_t new_conf) {
    const uint8_t old_rega = old_conf & 0xFF;
    const uint8_t new_rega = new_conf & 0xFF;
    if (old_rega != new_rega) USART0_REG_A = new_rega;

    const uint8_t old_regb = (old_conf >> 8) & 0xFF;
    const uint8_t new_regb = (new_conf >> 8) & 0xFF;
    if (old_regb != new_regb) USART0_REG_B = new_regb;

#if defined(USART0_REG_C)
    const uint8_t old_regc = (old_conf >> 16) & 0xFF;
    const uint8_t new_regc = (new_conf >> 16) & 0xFF;
    if (old_regc != new_regc) USART0_REG_C = new_regc;
#endif

#if defined(USART0_REG_D)
    const uint8_t old_regd = (old_conf >> 24) & 0xFF;
    const uint8_t new_regd = (new_conf >> 24) & 0xFF;
    if (old_regd != new_regd) USART0_REG_D = new_regd;
#endif
}


#ifdef usart0__double_speed__BIT
#define USART0_CONF_DOUBLE_SPEED                (USART0_CONF_BYTE_A(1<<usart0__double_speed__BIT))
#endif

#ifdef usart0__multiprocessor__BIT
#define USART0_CONF_MULTIPROCESSOR              (USART0_CONF_BYTE_A(1<<usart0__multiprocessor__BIT))
#endif


#define USART0_CONF_RX_COMPLETE_INT_ENABLED     (USART0_CONF_BYTE_B(1<<usart0__rx__complete__interrupt__enabled__BIT))
#define USART0_CONF_TX_COMPLETE_INT_ENABLED     (USART0_CONF_BYTE_B(1<<usart0__tx__complete__interrupt__enabled__BIT))
#define USART0_CONF_DATA_REG_EMPTY_INT_ENABLED  (USART0_CONF_BYTE_B(1<<usart0__data_register_empty__interrupt__enabled__BIT))
#define USART0_CONF_RX_ENABLED                  (USART0_CONF_BYTE_B(1<<usart0__rx__enabled__BIT))
#define USART0_CONF_TX_ENABLED                  (USART0_CONF_BYTE_B(1<<usart0__tx__enabled__BIT))


#if defined(USART0_REG_C)

#define USART0_CONF_MODE_ASYNC       	        (USART0_CONF_BYTE_C((0<<usart0__mode__BIT)))
#define USART0_CONF_MODE_SYNC                   (USART0_CONF_BYTE_C((1<<usart0__mode__BIT)))
#define USART0_CONF_MODE_RESERVED               (USART0_CONF_BYTE_C((2<<usart0__mode__BIT)))
#define USART0_CONF_MODE_SPI_MASTER             (USART0_CONF_BYTE_C((3<<usart0__mode__BIT)))

#define USART0_CONF_PARITY_DISABLED             (USART0_CONF_BYTE_C((0<<usart0__parity__BIT)))
#define USART0_CONF_PARITY_RESERVED             (USART0_CONF_BYTE_C((1<<usart0__parity__BIT)))
#define USART0_CONF_PARITY_EVEN                 (USART0_CONF_BYTE_C((2<<usart0__parity__BIT)))
#define USART0_CONF_PARITY_ODD                  (USART0_CONF_BYTE_C((3<<usart0__parity__BIT)))

#define USART0_CONF_STOP_BITS_1                 (USART0_CONF_BYTE_C(0<<usart0__stop_bits__BIT))
#define USART0_CONF_STOP_BITS_2                 (USART0_CONF_BYTE_C(1<<usart0__stop_bits__BIT))

#define USART0_CONF_POLARITY_0                  (USART0_CONF_BYTE_C(0<<usart0__polarity__BIT))
#define USART0_CONF_POLARITY_1                  (USART0_CONF_BYTE_C(1<<usart0__polarity__BIT))

#define USART0_CONF_CHAR_SIZE_5_BIT             (USART0_CONF_BYTE_B(0<<usart0__char_size2__BIT) | USART0_CONF_BYTE_C((0<<usart0__char_size0__BIT)))
#define USART0_CONF_CHAR_SIZE_6_BIT             (USART0_CONF_BYTE_B(0<<usart0__char_size2__BIT) | USART0_CONF_BYTE_C((1<<usart0__char_size0__BIT)))
#define USART0_CONF_CHAR_SIZE_7_BIT             (USART0_CONF_BYTE_B(0<<usart0__char_size2__BIT) | USART0_CONF_BYTE_C((2<<usart0__char_size0__BIT)))
#define USART0_CONF_CHAR_SIZE_8_BIT             (USART0_CONF_BYTE_B(0<<usart0__char_size2__BIT) | USART0_CONF_BYTE_C((3<<usart0__char_size0__BIT)))
#define USART0_CONF_CHAR_SIZE_RESERVED4         (USART0_CONF_BYTE_B(1<<usart0__char_size2__BIT) | USART0_CONF_BYTE_C((0<<usart0__char_size0__BIT)))
#define USART0_CONF_CHAR_SIZE_RESERVED5         (USART0_CONF_BYTE_B(1<<usart0__char_size2__BIT) | USART0_CONF_BYTE_C((1<<usart0__char_size0__BIT)))
#define USART0_CONF_CHAR_SIZE_RESERVED6         (USART0_CONF_BYTE_B(1<<usart0__char_size2__BIT) | USART0_CONF_BYTE_C((2<<usart0__char_size0__BIT)))
#define USART0_CONF_CHAR_SIZE_9_BIT             (USART0_CONF_BYTE_B(1<<usart0__char_size2__BIT) | USART0_CONF_BYTE_C((3<<usart0__char_size0__BIT)))

#else

#define USART0_CONF_CHAR_SIZE_8_BIT             (USART0_CONF_BYTE_B(0<<CHR9) | USART0_CONF_BYTE_B(1<<RXB8))
#define USART0_CONF_CHAR_SIZE_9_BIT             (USART0_CONF_BYTE_B(1<<CHR9) | USART0_CONF_BYTE_B(1<<RXB8))

#endif


#ifdef URSEL
#define USART0_CONF_DEFAULT                     (USART0_CONF_BYTE_C(1<<URSEL) | USART0_CONF_CHAR_SIZE_8_BIT)
#else
#define USART0_CONF_DEFAULT                     (USART0_CONF_CHAR_SIZE_8_BIT)
#endif


# if defined(usart0__double_speed__HOST) && defined(usart0__double_speed__BIT)
DEFINE_BITVAR(usart0__double_speed, usart0__double_speed__HOST, usart0__double_speed__BIT);
#endif

DEFINE_BITVAR(usart0__rx__enabled, usart0__rx__enabled__HOST, usart0__rx__enabled__BIT);
DEFINE_BITVAR(usart0__rx__frame_error, usart0__rx__frame_error__HOST, usart0__rx__frame_error__BIT);
DEFINE_BITVAR(usart0__rx__data_overrun, usart0__rx__data_overrun__HOST, usart0__rx__data_overrun__BIT);

# if defined(usart0__rx__parity_error__HOST) && defined(usart0__rx__parity_error__BIT)
DEFINE_BITVAR(usart0__rx__parity_error, usart0__rx__parity_error__HOST, usart0__rx__parity_error__BIT);
#endif

DEFINE_BITVAR(usart0__tx__enabled, usart0__tx__enabled__HOST, usart0__tx__enabled__BIT);
DEFINE_BITVAR(usart0__rx__complete__value, usart0__rx__complete__value__HOST, usart0__rx__complete__value__BIT);
DEFINE_BITVAR(usart0__rx__complete__interrupt__enabled, usart0__rx__complete__interrupt__enabled__HOST, usart0__rx__complete__interrupt__enabled__BIT);
DEFINE_BITVAR(usart0__tx__complete__value, usart0__tx__complete__value__HOST, usart0__tx__complete__value__BIT);
DEFINE_BITVAR(usart0__tx__complete__interrupt__enabled, usart0__tx__complete__interrupt__enabled__HOST, usart0__tx__complete__interrupt__enabled__BIT);
DEFINE_BITVAR(usart0__tx__data_register_empty__value, usart0__tx__data_register_empty__value__HOST, usart0__tx__data_register_empty__value__BIT);
DEFINE_BITVAR(usart0__tx__data_register_empty__interrupt__enabled, usart0__tx__data_register_empty__interrupt__enabled__HOST, usart0__tx__data_register_empty__interrupt__enabled__BIT);


// =============================================================================
// usart0__rate__set
// =============================================================================
#define USART0_DIVISOR(rate) ((F_CPU/8/(rate) - 1)/2)
#define CPU_PERIODS_PER_BIT_FROM_DIVISOR(divisor) (((divisor) * 2 + 1) * 8)

inline uint16_t UBRR_VALUE(const uint32_t rate) {
    return (uint16_t) USART0_DIVISOR(rate);
}

inline void usart0__divisor__set(const uint16_t divisor) {
#if defined(UBRR) || defined(UBRR0) || defined(UBRR1)
    USART0_BIT_RATE_REGISTER = (USART0_BIT_RATE_REGISTER_TYPE)(divisor);
#else
    UBRRH = (uint8_t)(divisor>>8);
    UBRRL = (uint8_t)(divisor);
#endif
}

inline void usart0__rate__set(const uint32_t rate) {
    usart0__divisor__set(UBRR_VALUE(rate));
}

// =============================================================================
// usart0__getc
// =============================================================================

#define USART0__GETC(result) __IN(result, USART0_DATA_REGISTER)

inline uint8_t usart0__getc(void) {
    return USART0_DATA_REGISTER;
}


// =============================================================================
// usart0__putc
// =============================================================================

#define USART0__PUTC(c) __OUT(USART0_DATA_REGISTER, c)

inline void usart0__putc(const uint8_t c) {
    // If using plain USART0_DATA_REGISTER=c, gcc inlines poorly,
    // places value to call parameter register anyway,
    // even if the value is in other fixed register
    // Most of the time, write is done with simple OUT/STS instruction
    // (may also base register pair + offset, although it is rare case)
    if (_SFR_MEM_ADDR(USART0_DATA_REGISTER) < 0x40) {
        __OUT(USART0_DATA_REGISTER, c);
    } else {
        __STS(USART0_DATA_REGISTER, c);
    }
}


// =============================================================================
// usart0__init
//
// Intitialises usart0: sets baud rate, specified in USART0__BAUD_RATE.
// 2X USART mode is used, only if 1X cannot be used.
// =============================================================================
#ifdef USART0__BAUD_RATE
inline void usart0__init(void) {
    __asm__ __volatile__("usart0__init:");
#if (F_CPU/8/USART0__BAUD_RATE) == 1
    usart0__rate__set(USART0__BAUD_RATE / 2);
    usart0__double_speed__set(1);
#elif (F_CPU/8/USART0__BAUD_RATE) > 1
    usart0__rate__set(USART0__BAUD_RATE);
#else
#error "Invalid baud rate"
#endif
}
#endif

#endif