#ifndef __CPU__AVR__USART0_RX_BUFFERED_H
#define __CPU__AVR__USART0_RX_BUFFERED_H

#include <stdint.h>


/**
 * Receives a byte from the USART0.
 * Blocks if no data available.
 */
uint8_t usart0__in__read(void);


#endif
