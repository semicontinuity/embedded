// =============================================================================
// USART receiver driver.
// =============================================================================

#ifndef SERVICES__USART_RX_H
#define SERVICES__USART_RX_H


void usart_rx__start(void);

void usart_rx__stop(void);

#ifdef USART_RX__DATA__REG
register uint8_t usart_rx__data asm(QUOTE(USART_RX__DATA__REG));
#endif

/**
 * Driver callback, to be implemented by user.
 */
void usart_rx__on_data(const uint8_t value);


#endif