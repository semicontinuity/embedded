// All source files to be compiled as one piece, to enabe cross-module function inlining
// And to ensure proper layout of buffers in memory

// Firmware
#include "can_tx_q.c"
#include "usart_tx.c"
#include "usart_tx_q.c"
#include "can_tx.c"
#include "usart_rx.c"
#include "usart_rx_buffer.c"
#include "router.c"
#include "server.c"
#include "main.c"

// BSP
#include "can.c"

// Library
#include "cpu/avr/drivers/net/can/mcp251x/operations.c"
