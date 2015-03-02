// =============================================================================
// MODBUS server.
// =============================================================================
#ifndef MODBUS_SERVER_H
#define MODBUS_SERVER_H

#include "modbus.h"
#include <stdbool.h>
#include <stdint.h>


// Function handlers to be implemented
// -----------------------------------------------------------------------------

#if defined(MODBUS_SERVER__HANDLE_READ_COILS) && MODBUS_SERVER__HANDLE_READ_COILS > 0
//modbus_exception modbus_server__read_coils(void);
#endif

#if defined(MODBUS_SERVER__HANDLE_READ_DISCRETE_INPUTS) && MODBUS_SERVER__HANDLE_READ_DISCRETE_INPUTS > 0
//modbus_exception modbus_server__read_discrete_inputs(void);
#endif

#if defined(MODBUS_SERVER__HANDLE_READ_HOLDING_REGISTERS) && MODBUS_SERVER__HANDLE_READ_HOLDING_REGISTERS > 0
modbus_exception modbus_server__read_holding_registers(uint16_t register_address, uint16_t register_count);
#endif

#if defined(MODBUS_SERVER__HANDLE_READ_INPUT_REGISTERS) && MODBUS_SERVER__HANDLE_READ_INPUT_REGISTERS > 0
modbus_exception modbus_server__read_input_registers(uint16_t register_address, uint16_t register_count);
#endif

#if defined(MODBUS_SERVER__HANDLE_WRITE_SINGLE_COIL) && MODBUS_SERVER__HANDLE_WRITE_SINGLE_COIL > 0
//modbus_exception modbus_server__write_single_coil(void);
#endif

#if defined(MODBUS_SERVER__HANDLE_WRITE_REGISTER) && MODBUS_SERVER__HANDLE_WRITE_REGISTER > 0
modbus_exception modbus_server__write_holding_register(uint16_t register_address, uint16_t register_value);
#endif


// Callbacks to be implemented
// -----------------------------------------------------------------------------

/** Called when a frame with valid length and CRC has been received */
void modbus_server__on_valid_frame_received(void);

/** Called when a frame with invalid length or CRC has been received */
void modbus_server__on_invalid_frame_received(void);

#endif