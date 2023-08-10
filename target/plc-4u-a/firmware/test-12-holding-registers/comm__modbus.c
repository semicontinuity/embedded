// =============================================================================
// Modbus communications.
// =============================================================================

#include "cpu/avr/asm.h"
#include "cpu/avr/drivers/comm/modbus/buffer.h"
#include "cpu/avr/drivers/comm/modbus/modbus_rtu_driver.h"
#include "cpu/avr/drivers/comm/modbus/modbus_server.h"

#include "services/discrete_outputs.h"
#include "services/internal_coils.h"


void modbus_rtu_driver__on_char_received(void) {
}

void modbus_rtu_driver__on_char_buffered(void) {
}

void modbus_rtu_driver__on_buffer_overflow(void) {
}

void modbus_rtu_driver__on_char_timeout(void) {
}

void modbus_rtu_driver__on_char_format_error(void) {
}

void modbus_rtu_driver__on_char_lost(void) {
}

void modbus_rtu_driver__on_frame_timeout(void) {
}

void modbus_rtu_driver__on_frame_processing(void) {
}

void modbus_rtu_driver__on_response(void) {
}

void modbus_rtu_driver__on_no_response(void) {
}

void modbus_rtu_driver__on_frame_sent(void) {
}

void modbus_rtu_driver__on_protocol_error(void) {
}

void modbus_server__on_valid_frame_received(void) {
}

void modbus_server__on_invalid_frame_received(void) {
}

// =============================================================================

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
modbus_exception modbus_server__read_holding_registers(uint16_t register_address, uint16_t register_count) {
    buffer__put_u8(holding_registers__bytes[0]);
    buffer__put_u8(holding_registers__bytes[1]);
    buffer__put_u8(holding_registers__bytes[2]);
    buffer__put_u8(holding_registers__bytes[3]);
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

    if (address == 0x00) discrete_output__0__set(active);
    if (address == 0x01) discrete_output__1__set(active);
    if (address == 0x02) discrete_output__2__set(active);
    if (address == 0x03) discrete_output__3__set(active);
    if (address == 0x04) discrete_output__4__set(active);
    if (address == 0x05) discrete_output__5__set(active);
    if (address == 0x06) discrete_output__6__set(active);
    if (address == 0x07) discrete_output__7__set(active);

    if (address == 0x08) discrete_output__8__set(active);
    if (address == 0x09) discrete_output__9__set(active);
    if (address == 0x0A) discrete_output__a__set(active);
    if (address == 0x0B) discrete_output__b__set(active);
    if (address == 0x0C) discrete_output__c__set(active);
    if (address == 0x0D) discrete_output__d__set(active);
    if (address == 0x0E) discrete_output__e__set(active);
    if (address == 0x0F) discrete_output__f__set(active);

    if (address == 0x10) internal_coil__0__set(active);
    if (address == 0x11) internal_coil__1__set(active);
    if (address == 0x12) internal_coil__2__set(active);
    if (address == 0x13) internal_coil__3__set(active);
    if (address == 0x14) internal_coil__4__set(active);
    if (address == 0x15) internal_coil__5__set(active);
    if (address == 0x16) internal_coil__6__set(active);
    if (address == 0x17) internal_coil__7__set(active);

    if (address == 0x18) internal_coil__8__set(active);
    if (address == 0x19) internal_coil__9__set(active);
    if (address == 0x1A) internal_coil__a__set(active);
    if (address == 0x1B) internal_coil__b__set(active);
    if (address == 0x1C) internal_coil__c__set(active);
    if (address == 0x1D) internal_coil__d__set(active);
    if (address == 0x1E) internal_coil__e__set(active);
    if (address == 0x1F) internal_coil__f__set(active);

    return MODBUS_EXCEPTION__NONE;
}
