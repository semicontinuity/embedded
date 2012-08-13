#ifndef __USART_RX_BUFFER_H
#define __USART_RX_BUFFER_H

#include <stdint.h>
#include "packet.h"


/*
 *****************************************************************************************************
 * USART RX Buffer:
 *
 * written by:	USART RX thread
 * read by:	'route' function
 *****************************************************************************************************
 */

extern uint8_t usart_rx_buffer[PACKET_LENGTH] __attribute__ ((section (".noinit")));


/**
 * Copy the usart_rx_buffer to the y register
 */
inline void usart_rx_buffer__to_y(void) {
    __asm__ __volatile__ (
        "ldi	r28, lo8(usart_rx_buffer)	\n\t"
        "ldi	r29, hi8(usart_rx_buffer)	\n\t"
    );
}


#endif // __USART_RX_BUFFER_H