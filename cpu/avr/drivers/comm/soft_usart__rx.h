// =============================================================================
// Software USART driver, receiver module.
// =============================================================================

#ifndef CPU__AVR__DRIVERS__COMM__SOFT_USART__RX_H
#define CPU__AVR__DRIVERS__COMM__SOFT_USART__RX_H


void soft_usart__rx__start(void);

void soft_usart__rx__stop(void);

void soft_usart__rx__run(void);

/** Invoked when the start of character is detected */
void soft_usart__rx__signal(void);

#endif
