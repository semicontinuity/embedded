// =============================================================================
// MODBUS RTU driver.
// USART receiver module.
// =============================================================================

#ifndef MODBUS_RTU_DRIVER__USART_RX_H
#define MODBUS_RTU_DRIVER__USART_RX_H

#include <stdbool.h>


void modbus_rtu_driver__usart_rx__start(void);

void modbus_rtu_driver__usart_rx__stop(void);

void modbus_rtu_driver__usart_rx__enable(void);

void modbus_rtu_driver__usart_rx__disable(void);

/**
 * Called when data received would overflow the buffer.
 * To be implemented by user.
 */
void modbus_rtu_driver__usart_rx__on_buffer_overflow(void);

/**
 * Called when data are received when they should not be.
 * To be implemented by user.
 */
void modbus_rtu_driver__usart_rx__on_unexpected_data(void);


#endif