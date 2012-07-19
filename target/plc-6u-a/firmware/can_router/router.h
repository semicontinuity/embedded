#ifndef __ROUTE_H
#define __ROUTE_H

#include "usart_rx_buffer.h"

void router__process_packet(void) __attribute__((noinline));

#endif // __ROUTE_H