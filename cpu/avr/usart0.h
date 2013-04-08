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
// =============================================================================

#ifndef __CPU__AVR__USART0_H
#define __CPU__AVR__USART0_H

#include <stdint.h>
#include <avr/sfr_defs.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "cpu/avr/gpio.h"



#if defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__) || defined(__AVR_ATmega168__) || \
    defined(__AVR_ATmega48P__) || defined(__AVR_ATmega88P__) || defined(__AVR_ATmega168P__)


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


#if defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__) || defined(__AVR_ATmega168__) || \
    defined(__AVR_ATmega48P__) || defined(__AVR_ATmega88P__) || defined(__AVR_ATmega168P__)

inline void usart0__rate__set(uint32_t rate) {
    UBRR0H = (uint8_t)(UBRR_VALUE(rate)>>8);
    UBRR0L = (uint8_t)(UBRR_VALUE(rate));
}

#elif defined(__AVR_ATmega8__) || defined(__AVR_ATmega16__)

inline void usart0__rate__set(uint32_t rate) {
    UBRRH = (uint8_t)(UBRR_VALUE(rate)>>8);
    UBRRL = (uint8_t)(UBRR_VALUE(rate));
}

#elif defined(__AVR_AT90S2313__)

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
#if defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__) || defined(__AVR_ATmega168__) || \
    defined(__AVR_ATmega48P__) || defined(__AVR_ATmega88P__) || defined(__AVR_ATmega168P__)
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
#if defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__) || defined(__AVR_ATmega168__) || \
    defined(__AVR_ATmega48P__) || defined(__AVR_ATmega88P__) || defined(__AVR_ATmega168P__)
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
#if defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__) || defined(__AVR_ATmega168__) || \
    defined(__AVR_ATmega48P__) || defined(__AVR_ATmega88P__) || defined(__AVR_ATmega168P__)
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
#if defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__) || defined(__AVR_ATmega168__) || \
    defined(__AVR_ATmega48P__) || defined(__AVR_ATmega88P__) || defined(__AVR_ATmega168P__)
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
#if defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__) || defined(__AVR_ATmega168__) || \
    defined(__AVR_ATmega48P__) || defined(__AVR_ATmega88P__) || defined(__AVR_ATmega168P__)
    set_bit_in_reg(UCSR0B, TXEN0);
#elif defined(__AVR_ATmega8__) || defined(__AVR_ATmega16__)
    set_bit_in_reg(UCSRB, TXEN);
#else
    #error "Unsupported MCU"
#endif
}


// =============================================================================
// usart0__out__write
// =============================================================================

inline void usart0__out__write(char c) {
#if defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__) || defined(__AVR_ATmega168__) || \
    defined(__AVR_ATmega48P__) || defined(__AVR_ATmega88P__) || defined(__AVR_ATmega168P__)
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = c;
#elif defined(__AVR_ATmega8__) || defined(__AVR_ATmega16__)
    loop_until_bit_is_set(UCSRA, UDRE);
    UDR = c;
#else
    #error "Unsupported MCU"
#endif
}


// =============================================================================
// usart0__out__send
// =============================================================================

inline void usart0__out__send(const char *data, uint8_t count) {
    // synchronously
    do {
        // do not inline 'b', compile will produce less optimal code.
        char b = *data++;
        usart0__out__write(b);
    }
    while (--count > 0);
}


#endif