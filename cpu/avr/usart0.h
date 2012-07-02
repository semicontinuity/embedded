// =============================================================================
// USART0
//
// API:
//
// usart__rate__set:
//   Sets the USART bit rate
//
// usart_init:
//   Initialize the USART to typical mode: Async, 8 bit, no parity, 1 stop bit.
//
// usart_in__read:
//   Blocking read
//
// usart_out__write:
//   Blocking write
// =============================================================================

#ifndef __CPU_AVR_UART0_H
#define __CPU_AVR_UART0_H

#include "device.h"

#include <stdint.h>
#include <avr/sfr_defs.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "cpu/avr/gpio.h"



// =============================================================================
// usart__rate__set
// =============================================================================
#define UBRR_VALUE(baud) ((F_CPU/8/(baud) - 1)/2)

#if defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__) ||\
    defined(__AVR_ATmega168__) || defined(__AVR_ATmega8__)

inline void usart__rate__set(uint16_t rate) {
    UBRRH = (uint8_t)(UBRR_VALUE(rate)/256);
    UBRRL = (uint8_t)(UBRR_VALUE(rate));
}

#elif defined(__AVR_AT90S2313__)

inline void usart__rate__set(uint8_t rate) {
    UBRR=(UBRR_VALUE(rate));
}

#else
    #error "Unsupported MCU"
#endif


// =============================================================================
// usart_init
// =============================================================================

inline void usart__init(void) {
//           Asynch UART               No parity             1 stopbit  8 bit(+reg B)   polarity
#if defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__) ||\
    defined(__AVR_ATmega168__) 

//  UMSEL=00	Asynch UART
//  UPM=00	No Parity
//  USBS=0	1 stop bit
//  UCSZ=011	8 bit
//  UCPOL0=0	Polarity: Rising, 0 for Asynch.
    UCSR0C = (0<<UMSEL01)|(0<<UMSEL00)|(0<<UPM01)|(0<<UPM00)|(0<<USBS)|(3<<UCSZ0)|(0<<UCPOL);
#elif defined(__AVR_ATmega8__)
    UCSRC = (1<<URSEL)|(0<<UMSEL)|(0<<UPM1)|(0<<UPM0)|(0<<USBS)|(3<<UCSZ0)|(0<<UCPOL);
#else
    #error "Unsupported MCU"
#endif
}


// =============================================================================
// usart__in__enabled__set
// =============================================================================

inline void usart__in__enabled__set(void) {
#if defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__) ||\
    defined(__AVR_ATmega168__) 
    set_bit_in_reg(UCSR0B, RXEN0);
#elif defined(__AVR_ATmega8__)
    set_bit_in_reg(UCSRB, RXEN);
#else
    #error "Unsupported MCU"
#endif
}


// =============================================================================
// usart__in__complete__set
// =============================================================================

inline void usart__in__complete__set(void) {
#if defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__) ||\
    defined(__AVR_ATmega168__) 
    set_bit_in_reg(UCSR0B, RXCIE0);
#elif defined(__AVR_ATmega8__)
    set_bit_in_reg(UCSRB, RXCIE);
#else
    #error "Unsupported MCU"
#endif
}


// =============================================================================
// usart__out__enabled__set
// =============================================================================

inline void usart__out__enabled__set(void) {
#if defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__) ||\
    defined(__AVR_ATmega168__) 
    set_bit_in_reg(UCSR0B, TXEN0);
#elif defined(__AVR_ATmega8__)
    set_bit_in_reg(UCSRB, TXEN);
#else
    #error "Unsupported MCU"
#endif
}

// =============================================================================
// usart_in__read
// =============================================================================

inline char usart__in__read(void) {
#if defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__) ||\
    defined(__AVR_ATmega168__) 
    loop_until_bit_is_set(UCSR0A, RXC0);
    return UDR0;
#elif defined(__AVR_ATmega8__)
    loop_until_bit_is_set(UCSRA, RXC);
    return UDR;
#else
    #error "Unsupported MCU"
#endif
}


// =============================================================================
// usart_out__write
// =============================================================================

inline void usart__out__write(char c) {
#if defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__) ||\
    defined(__AVR_ATmega168__) 
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UCSR0C = (0<<UMSEL01)|(0<<UMSEL00)|(0<<UPM01)|(0<<UPM00)|(0<<USBS)|(3<<UCSZ0)|(0<<UCPOL);
    UDR = c;
#elif defined(__AVR_ATmega8__)
    loop_until_bit_is_set(UCSRA, UDRE);
    UCSRC = (1<<URSEL)|(0<<UMSEL)|(0<<UPM1)|(0<<UPM0)|(0<<USBS)|(3<<UCSZ0)|(0<<UCPOL);
    UDR = c;
#else
    #error "Unsupported MCU"
#endif
}


#endif