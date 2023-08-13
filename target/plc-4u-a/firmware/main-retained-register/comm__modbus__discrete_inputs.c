// =============================================================================
// Modbus communications.
// Discrete inputs support.
// =============================================================================

#include "cpu/avr/drivers/comm/modbus/buffer.h"
#include "cpu/avr/drivers/comm/modbus/modbus_server.h"

#include "services/discrete_inputs.h"


/**
 * Process READ DISCRETE INPUTS request.
 * Reads all discrete inputs at once!
 * Buffer write pointer: after BYTE COUNT field (already written), ready to write bytes with input bits.
 * Write exactly MODBUS_SERVER__DISCRETE_INPUTS_COUNT bits to the buffer.
 * Returns:
 *   Code: modbus_exception
 *   If OK:
 *     Buffer: populated with response bytes except CRC; buffer write position: after payload bytes.
 *       Payload: [BYTE_COUNT_TO_FOLLOW][BYTES...]
 *   Else:
 *     Buffer: retain address and function code.
 */
modbus_exception modbus_server__read_discrete_inputs(void) {
    __asm__ __volatile__( "modbus_server__read_discrete_inputs:");
    buffer__put_u8(discrete_inputs__byte0);
    buffer__put_u8(discrete_inputs__byte1);
    __asm__ __volatile__( "modbus_server__read_discrete_inputs__done:");
    return MODBUS_EXCEPTION__NONE;
}
