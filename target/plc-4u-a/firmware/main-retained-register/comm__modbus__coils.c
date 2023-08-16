// =============================================================================
// Modbus communications.
// Coils support.
// =============================================================================

#include "cpu/avr/drivers/comm/modbus/modbus_server.h"
#include "cpu/avr/drivers/comm/modbus/buffer.h"
#include "services/discrete_outputs.h"
#include "services/internal_coils.h"


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
modbus_exception modbus_server__read_coils(void) {
    __asm__ __volatile__( "modbus_server__read_coils:");
    buffer__put_u8(discrete_outputs__byte0);
    buffer__put_u8(discrete_outputs__byte1);
    buffer__put_u8(internal_coils__byte0);
    buffer__put_u8(internal_coils__byte1);
    __asm__ __volatile__( "modbus_server__read_coils__done:");
    return MODBUS_EXCEPTION__NONE;
}


/**
 * Process WRITE SINGLE COIL request.
 * Buffer: do not read or write.
 * Returns:
 *   Code: modbus_exception
 */
modbus_exception modbus_server__write_single_coil(uint16_t address, uint8_t active) {
    __asm__ __volatile__( "modbus_server__write_single_coil:");

    if (address < 0x10) discrete_outputs__set(address, active);
    else if (address < 0x20) internal_coils__set(address - 0x10, active);

    return MODBUS_EXCEPTION__NONE;
}
