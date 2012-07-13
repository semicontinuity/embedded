// All source files to be compiled as one piece, to enabe cross-module function inlining
// And to ensure proper layout of buffers in memory

#include "usart_tx.c"
#include "can_tx.c"
#include "usart_rx.c"
#include "usart_rx_buffer.c"
#include "route.c"
#include "main.c"

#include "can.c"

#include "cpu/avr/drivers/net/can/mcp251x/operations.c"
