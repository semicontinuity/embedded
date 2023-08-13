// =============================================================================
// MODBUS RTU driver.
// =============================================================================
#ifndef CPU__AVR__DRIVERS__COMM__MODBUS__MODBUS_RTU_DRIVER_H
#define CPU__AVR__DRIVERS__COMM__MODBUS__MODBUS_RTU_DRIVER_H

#include <stdbool.h>
#include <stdint.h>


void modbus_rtu_driver__init(void);

void modbus_rtu_driver__configure(const uint16_t divisor);

void modbus_rtu_driver__start(void);
void modbus_rtu_driver__stop(void);

bool modbus_rtu_driver__is_runnable(void);

void modbus_rtu_driver__run(void);


// Callback methods to be implemented by user
// -----------------------------------------------------------------------------

/**
 * Invoked by the driver on every received frame.
 *
 * @return true if the response must be sent (placed to the same buffer)
 */
bool modbus_rtu_driver__on_frame_received(void);


void modbus_rtu_driver__on_frame_sent(void);

/**
 * Invoked by the driver, when data are received when they should not be.
 */
void modbus_rtu_driver__on_protocol_error(void);

void modbus_rtu_driver__on_buffer_overflow(void);

/**
 * Invoked by the driver, when a character is received.
 */
void modbus_rtu_driver__on_char_received(void);

/**
 * Invoked by the driver, when reception is enabled and a character is placed to buffer.
 */
void modbus_rtu_driver__on_char_buffered(void);

/**
 * Invoked by the driver, when character timeout (normally 1.5 characters) has expired.
 */
void modbus_rtu_driver__on_char_timeout(void);

void modbus_rtu_driver__on_char_format_error(void);

void modbus_rtu_driver__on_char_lost(void);

/**
 * Invoked by the driver, when frame timeout (normally 3.5 characters) has expired.
 */
void modbus_rtu_driver__on_frame_timeout(void);

void modbus_rtu_driver__on_frame_processing(void);

void modbus_rtu_driver__on_response(void);

/**
 * Invoked by the driver, when the frame is received, but no response will be sent.
 * (E.g., on address mismatch, CRC mismatch, incorrect size)
 */
void modbus_rtu_driver__on_no_response(void);


#endif