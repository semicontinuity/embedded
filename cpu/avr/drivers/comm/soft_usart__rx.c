// =============================================================================
// Software USART driver, receiver module.
// Implemented with TIMER 0.
// =============================================================================

#include "cpu/avr/drivers/comm/soft_usart__rx.h"


#ifdef SOFT_USART__RX__DATA__REG
register uint8_t soft_usart__rx__data asm(QUOTE(SOFT_USART__RX__DATA__REG));
#else
volatile uint8_t soft_usart__rx__data;
#endif

#ifdef SOFT_USART__RX__INDEX__REG
register  int8_t soft_usart__rx__index asm(QUOTE(SOFT_USART__RX__INDEX__REG));
#else
volatile  int8_t soft_usart__rx__index;
#endif


void soft_usart__rx__start(void) {
}


void soft_usart__rx__stop(void) {
}


/**
 * Invoked periodically by the associated timer (if it is started)
 * with the delay, equal to 1 bit time, before every data bit, before and after stop bit.
 * During every invocation, the output pin will be driven according to the value of the corresponding bit.
 */
void soft_usart__rx__run(void) {
}


/** Invoked when the start of character is detected */
void soft_usart__rx__signal(void) {
}
