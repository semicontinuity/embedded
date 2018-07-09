// =============================================================================
// MODBUS RTU driver.
// USART receiver module.
// =============================================================================

#ifndef CPU__AVR__DRIVERS__COMM__MODBUS__MODBUS_RTU_DRIVER__USART_RX_H
#define CPU__AVR__DRIVERS__COMM__MODBUS__MODBUS_RTU_DRIVER__USART_RX_H

#include <stdbool.h>


void modbus_rtu_driver__usart_rx__start(void);

void modbus_rtu_driver__usart_rx__stop(void);

void modbus_rtu_driver__usart_rx__enable(void);

void modbus_rtu_driver__usart_rx__disable(void);


// Callback methods to be implemented
// -----------------------------------------------------------------------------

/**
 * Invoked when a character is received.
 */
void modbus_rtu_driver__usart_rx__on_char_received(void);

/**
 * Invoked when reception is enabled and a character is placed to buffer.
 */
void modbus_rtu_driver__usart_rx__on_char_buffered(void);

/**
 * Invoked when a character format error is detected.
 */
void modbus_rtu_driver__usart_rx__on_char_format_error(void);

/**
 * Invoked when a character is lost.
 */
void modbus_rtu_driver__usart_rx__on_char_lost(void);

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