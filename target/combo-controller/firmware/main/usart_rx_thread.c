/*
 *****************************************************************************************************
 * USART RX Thread
 *****************************************************************************************************
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include "cpu/avr/usart0.h"
#include "util/bitops.h"


#define USART_RX_THREAD_INTERRUPT	ISR(USART_RXC_vect, USART_RX_vect_attrs)


USART_RX_THREAD_INTERRUPT {
    usart_rx_q__put(usart0__in__peek());
}
