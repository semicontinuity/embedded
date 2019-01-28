/*
 *****************************************************************************************************
 * Notifications sender that uses TX buffer 2.
 * Transmits notifications with USART data.
 *****************************************************************************************************
 */

#include <avr/interrupt.h>
#include "usart_rx_q.h"
#include "drivers/net/can/mcp251x/tx.h"

/**
 * Transmits notification with USART data.
 * Invoked when TX buffer 2 is available and there are data to transmit (= interrupt enabled).
 */
ISR(INT2_vect) {
    mcp2515__tx__txb2__load_data(usart_rx_q__r_ptr, 1);
    mcp2515__tx__txb2__request_to_send();
}
