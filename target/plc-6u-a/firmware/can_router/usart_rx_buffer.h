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


#endif // __USART_RX_BUFFER_H