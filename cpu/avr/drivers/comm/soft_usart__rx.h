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

// Callbacks to be implemented
// -----------------------------------------------------------------------------

/** Invoked to start periodic timer associated with TX module */
void soft_usart__tx__timer__start(void);

/** Invoked to stop periodic timer associated with TX module */
void soft_usart__tx__timer__stop(void);


#endif
