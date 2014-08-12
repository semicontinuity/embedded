// =============================================================================
// Software USART driver, timer module.
// =============================================================================

#ifndef CPU__AVR__DRIVERS__COMM__SOFT_USART__RX_H
#define CPU__AVR__DRIVERS__COMM__SOFT_USART__RX_H


void soft_usart__timer__init(void);

void soft_usart__timer__signal_start_bit_begin(void);

void soft_usart__timer__signal_start_bit_middle(void);

void soft_usart__timer__signal_stop_bit_middle(void);

#endif
