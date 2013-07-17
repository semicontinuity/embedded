/*
 *****************************************************************************************************
 * USART RX Queue
 *****************************************************************************************************
 */
#include "usart_rx_q.h"

uint8_t usart_rx_q[USART_RX_Q_SIZE_BYTES];
uint8_t *usart_rx_q__r_ptr;
uint8_t *usart_rx_q__w_ptr;
uint8_t *usart_rx_q__size;


void usart_rx_q__put(const uint8_t c) {
    *usart_rx_q__w_ptr = c;
    if (usart_rx_q__w_ptr == &usart_rx_q[USART_RX_Q_SIZE_BYTES - 1]) {
        usart_rx_q__w_ptr = &usart_rx_q[0];
    }
    else {
        usart_rx_q__w_ptr++;
    }
#ifdef usart_rx_q__on_put
    usart_rx_q__on_put();
#endif
}

