// =============================================================================
// USART transmitter
// =============================================================================

#ifndef MODBUS_RTU_DRIVER__USART_TX_H
#define MODBUS_RTU_DRIVER__USART_TX_H

#include <stdbool.h>


void modbus_rtu_driver__usart_tx__start(void);


void modbus_rtu_driver__usart_tx__stop(void);


void modbus_rtu_driver__usart_tx__enable(void);


void modbus_rtu_driver__usart_tx__disable(void);


/** Callback to be implemented */
void modbus_rtu_driver__usart_tx__on_frame_sent(void);

#endif