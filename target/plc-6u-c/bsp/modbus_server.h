// =============================================================================
// MODBUS server.
// =============================================================================
#ifndef MODBUS_SERVER_H
#define MODBUS_SERVER_H

#include "modbus.h"
#include <stdbool.h>
#include <stdint.h>


// Callbacks to be implemented
// -----------------------------------------------------------------------------

#if defined(MODBUS_SERVER__HANDLE_READ_COILS) && MODBUS_SERVER__HANDLE_READ_COILS > 0
modbus_exception modbus_server__handle_read_coils(void);
#endif

#if defined(MODBUS_SERVER__HANDLE_READ_DISCRETE_INPUTS) && MODBUS_SERVER__HANDLE_READ_DISCRETE_INPUTS > 0
modbus_exception modbus_server__handle_read_discrete_inputs(void);
#endif

#if defined(MODBUS_SERVER__HANDLE_READ_HOLDING_REGISTERS) && MODBUS_SERVER__HANDLE_READ_HOLDING_REGISTERS > 0
modbus_exception modbus_server__handle_read_holding_registers(void);
#endif

#if defined(MODBUS_SERVER__HANDLE_READ_INPUT_REGISTERS) && MODBUS_SERVER__HANDLE_READ_INPUT_REGISTERS > 0
modbus_exception modbus_server__handle_read_input_registers(void);
#endif

#if defined(MODBUS_SERVER__HANDLE_WRITE_SINGLE_COIL) && MODBUS_SERVER__HANDLE_WRITE_SINGLE_COIL > 0
modbus_exception modbus_server__handle_write_single_coil(void);
#endif

#if defined(MODBUS_SERVER__HANDLE_WRITE_REGISTER) && MODBUS_SERVER__HANDLE_WRITE_REGISTER > 0
modbus_exception modbus_server__handle_write_register(void);
#endif


#endif