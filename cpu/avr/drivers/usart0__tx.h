// =============================================================================
// Generic USART0 interrupt-based driver for transmission.
// =============================================================================

#ifndef CPU__AVR__DRIVERS__USART0__TX_H
#define CPU__AVR__DRIVERS__USART0__TX_H


#include <stdint.h>
#include <stdbool.h>

void usart0__tx__start(void);

void usart0__tx__stop(void);

#ifdef USART0__TX__DATA__REG
register uint8_t usart0__tx__data asm(QUOTE(USART0__TX__DATA__REG));
#endif

/**
 * Driver callback, to be implemented by user.
 */
bool usart0__tx__has_next(void);

/**
 * Driver callback, to be implemented by user.
 */
uint8_t usart0__tx__next(void);

/**
 * Driver callback, to be implemented by user.
 */
void usart0__tx__on_done(void);


#endif