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
    uint8_t *p = holding_registers__buffer;
    for (uint8_t a = 0; a < MODBUS_SERVER__HOLDING_REGISTERS_COUNT << 1; a++) {
        buffer__put_u8(*p++);
    }
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
