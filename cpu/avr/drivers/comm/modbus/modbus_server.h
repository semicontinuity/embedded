// =============================================================================
// MODBUS server.
// =============================================================================
#ifndef CPU__AVR__DRIVERS__COMM__MODBUS__MODBUS_SERVER_H
#define CPU__AVR__DRIVERS__COMM__MODBUS__MODBUS_SERVER_H

#include "cpu/avr/drivers/comm/modbus/modbus.h"
#include <stdbool.h>
#include <stdint.h>


// Function handlers to be implemented
// -----------------------------------------------------------------------------

#if defined(MODBUS_SERVER__HANDLE_READ_COILS) && MODBUS_SERVER__HANDLE_READ_COILS > 0
/**
 * Process READ COILS request.
 * Reads all coils at once!
 * Buffer write pointer: after BYTE COUNT field (already written), ready to write bytes with coil bits.
 * Write exactly MODBUS_SERVER__COIL_COUNT bits to the buffer.
 * Returns:
 *   Code: modbus_exception
 *   If OK:
 *     Buffer: populated with response bytes except CRC; buffer write position: after payload bytes.
 *       Payload: [BYTE_COUNT_TO_FOLLOW][BYTES...]
 *   Else:
 *     Buffer: retain address and function code.
 */
modbus_exception modbus_server__read_coils(void);
#endif

#if defined(MODBUS_SERVER__HANDLE_READ_DISCRETE_INPUTS) && MODBUS_SERVER__HANDLE_READ_DISCRETE_INPUTS > 0
/**
 * Process READ DESCRETE INPUTS request.
 * Reads all discrete inputs at once!
 * Buffer write pointer: after BYTE COUNT field (already written), ready to write bytes with input bits.
 * Write exactly MODBUS_SERVER__DISCRETE_INPUT_COUNT bits to the buffer.
 * Returns:
 *   Code: modbus_exception
 *   If OK:
 *     Buffer: populated with response bytes except CRC; buffer write position: after payload bytes.
 *       Payload: [BYTE_COUNT_TO_FOLLOW][BYTES...]
 *   Else:
 *     Buffer: retain address and function code.
 */
modbus_exception modbus_server__read_discrete_inputs(void);
#endif

#if defined(MODBUS_SERVER__HANDLE_READ_HOLDING_REGISTERS) && MODBUS_SERVER__HANDLE_READ_HOLDING_REGISTERS > 0
/**
 * Process READ HOLDING REGISTERS request.
 * Buffer write position: after BYTE COUNT field (already written), ready to write holding register bytes.
 * Returns:
 *   Code: modbus_exception
 *   If OK:
 *     Buffer: populated with response bytes except CRC; buffer write position: after payload bytes.
 *       Payload: [BYTE_COUNT_TO_FOLLOW][BYTES...]
 *   Else:
 *     Buffer: retain address and function code.
 */
modbus_exception modbus_server__read_holding_registers(uint16_t register_address, uint16_t register_count);
#endif

#if defined(MODBUS_SERVER__HANDLE_READ_INPUT_REGISTERS) && MODBUS_SERVER__HANDLE_READ_INPUT_REGISTERS > 0
/**
 * Process READ INPUT REGISTERS request.
 * Buffer write position: after BYTE COUNT field (already written), ready to write holding register bytes.
 * Returns:
 *   Code: modbus_exception
 *   If OK:
 *     Buffer: populated with response bytes except CRC; buffer write position: after payload bytes.
 *       Payload: [BYTE_COUNT_TO_FOLLOW][BYTES...]
 *   Else:
 *     Buffer: retain address and function code.
 */
modbus_exception modbus_server__read_input_registers(uint16_t register_address, uint16_t register_count);
#endif

#if defined(MODBUS_SERVER__HANDLE_WRITE_SINGLE_COIL) && MODBUS_SERVER__HANDLE_WRITE_SINGLE_COIL > 0
/**
 * Process WRITE SINGLE COIL request.
 * Buffer: do not read or write.
 * Returns:
 *   Code: modbus_exception
 */
modbus_exception modbus_server__write_single_coil(uint16_t register_address, uint8_t active);
#endif

#if defined(MODBUS_SERVER__HANDLE_WRITE_REGISTER) && MODBUS_SERVER__HANDLE_WRITE_REGISTER > 0
/**
 * Process WRITE HOLDING REGISTER request.
 * Buffer: do not read or write.
 * Returns:
 *   Code: modbus_exception
 */
modbus_exception modbus_server__write_holding_register(uint16_t register_address, uint16_t register_value);
#endif


// Callbacks to be implemented
// -----------------------------------------------------------------------------

/** Called when a frame with valid length and CRC has been received */
void modbus_server__on_valid_frame_received(void);

/** Called when a frame with invalid length or CRC has been received */
void modbus_server__on_invalid_frame_received(void);

#endif
