// =============================================================================
// USART0 receiver driver.
// =============================================================================

#ifndef CPU__AVR__DRIVERS__USART0__RX_H
#define CPU__AVR__DRIVERS__USART0__RX_H


void usart0__rx__start(void);

void usart0__rx__stop(void);

#ifdef USART0__RX__DATA__REG
register uint8_t usart0__rx__data asm(QUOTE(USART0__RX__DATA__REG));
#endif

/**
 * Driver callback, to be implemented by user.
 */
void usart0__rx__on_data(const uint8_t value);


#endif