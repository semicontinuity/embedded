#include "usart_rx_buffer.h"
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

uint8_t usart_rx_buffer[PACKET_LENGTH] __attribute__ ((section (".noinit")));
