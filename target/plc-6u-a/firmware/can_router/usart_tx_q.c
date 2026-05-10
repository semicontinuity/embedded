#include "usart_tx.h"
#include "usart_tx_q.h"

uint8_t usart_tx_q[USART_TX_Q_SIZE_BYTES] __attribute__((section(".usart_tx_q")));
