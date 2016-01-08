// =============================================================================
// MODBUS RTU driver.
// USART transmitter module.
// =============================================================================

#ifndef MODBUS_RTU_DRIVER__USART_TX_H
#define MODBUS_RTU_DRIVER__USART_TX_H

#include <stdbool.h>


void modbus_rtu_driver__usart_tx__start(void);


void modbus_rtu_driver__usart_tx__stop(void);


void modbus_rtu_driver__usart_tx__signal(void);



/**
 * Called when the buffer has been fully transmitted.
 * To be implemented by user.
 */
void modbus_rtu_driver__usart_tx__on_frame_sent(void);


#endif