// =============================================================================
// Software USART driver, transmitter module.
// =============================================================================

#ifndef CPU__AVR__DRIVERS__COMM__SOFT_USART__TX_H
#define CPU__AVR__DRIVERS__COMM__SOFT_USART__TX_H

#include <stdint.h>


void soft_usart__tx__start(void);

void soft_usart__tx__stop(void);

/** Request to start transmission of a byte of data */
void soft_usart__tx__write(const uint8_t data);

/** Invoked periodically by the associated timer (if it is started) with the delay equal to 1 bit time */
void soft_usart__tx__run(void);


// Callbacks to be implemented
// -----------------------------------------------------------------------------

/** Invoked when the byte of data has been fully transmitted */
void soft_usart__tx__on_write_complete(void);

/** Invoked to start periodic timer associated with TX module */
void soft_usart__tx__timer__start(void);

/** Invoked to stop periodic timer associated with TX module */
void soft_usart__tx__timer__stop(void);

#endif
