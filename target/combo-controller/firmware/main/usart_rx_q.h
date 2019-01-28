/*
 *****************************************************************************************************
 * USART RX Queue
 *****************************************************************************************************
 */
#ifndef __USART_RX_Q_H
#define __USART_RX_Q_H

#include <stdint.h>

extern uint8_t usart_rx_q[USART_RX_Q_SIZE_BYTES];
extern uint8_t *usart_rx_q__r_ptr;
extern uint8_t *usart_rx_q__w_ptr;
extern uint8_t *usart_rx_q__size;


void usart_rx_q__put(const uint8_t c);

#ifdef usart_rx_q__on_put
void usart_rx_q__on_put(void);
#endif

#endif
