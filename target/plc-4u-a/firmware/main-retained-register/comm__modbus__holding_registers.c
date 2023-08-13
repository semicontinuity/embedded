// =============================================================================
// Modbus communications.
// Holding registers support.
// =============================================================================

#include "cpu/avr/drivers/comm/modbus/modbus_server.h"
#include "cpu/avr/drivers/comm/modbus/buffer.h"
#include "services/holding_registers.h"


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
modbus_exception modbus_server__read_holding_registers(void) {
    buffer__put_u8(holding_registers__buffer[0]);
    buffer__put_u8(holding_registers__buffer[1]);

    buffer__put_u8(holding_registers__buffer[2]);
    buffer__put_u8(holding_registers__buffer[3]);

    buffer__put_u8(holding_registers__buffer[4]);
    buffer__put_u8(holding_registers__buffer[5]);

    buffer__put_u8(holding_registers__buffer[6]);
    buffer__put_u8(holding_registers__buffer[7]);

    buffer__put_u8(holding_registers__buffer[8]);
    buffer__put_u8(holding_registers__buffer[9]);

    buffer__put_u8(holding_registers__buffer[10]);
    buffer__put_u8(holding_registers__buffer[11]);

    buffer__put_u8(holding_registers__buffer[12]);
    buffer__put_u8(holding_registers__buffer[13]);

    return MODBUS_EXCEPTION__NONE;
}


/**
 * Process WRITE HOLDING REGISTER request.
 * Buffer: do not read or write.
 * Returns:
 *   Code: modbus_exception
 */
modbus_exception modbus_server__write_holding_register(uint16_t register_address, uint16_t register_value) {
    __asm__ __volatile__("modbus_server__write_holding_register:");
    holding_registers__set(register_address, register_value);
    return MODBUS_EXCEPTION__NONE;
}
