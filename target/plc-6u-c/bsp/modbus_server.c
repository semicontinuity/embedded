// =============================================================================
// MODBUS server.
// =============================================================================

#include "modbus_server.h"
#include "buffer.h"
#include "modbus_rtu_driver.h"
#include "util/crc16_table2x256.h"


modbus_exception modbus_server__process_frame(void) {
    switch (buffer__data[MODBUS_FRAME_OFFSET_FUNCTION]) {
#if defined(MODBUS_SERVER__HANDLE_READ_COILS) && MODBUS_SERVER__HANDLE_READ_COILS > 0
    case MODBUS_FUNCTION_READ_COILS:
        return modbus_server__handle_read_coils();
#endif

#if defined(MODBUS_SERVER__HANDLE_READ_DISCRETE_INPUTS) && MODBUS_SERVER__HANDLE_READ_DISCRETE_INPUTS > 0
        return modbus_server__handle_read_discrete_inputs();
    case MODBUS_FUNCTION_READ_DISCRETE_INPUTS:
#endif

#if defined(MODBUS_SERVER__HANDLE_READ_HOLDING_REGISTERS) && MODBUS_SERVER__HANDLE_READ_HOLDING_REGISTERS > 0
    case MODBUS_FUNCTION_READ_HOLDING_REGISTERS:
        return modbus_server__handle_read_holding_registers();
#endif

#if defined(MODBUS_SERVER__HANDLE_READ_INPUT_REGISTERS) && MODBUS_SERVER__HANDLE_READ_INPUT_REGISTERS > 0
    case MODBUS_FUNCTION_READ_INPUT_REGISTERS:
        return modbus_server__handle_read_input_registers();
#endif

#if defined(MODBUS_SERVER__HANDLE_WRITE_SINGLE_COIL) && MODBUS_SERVER__HANDLE_WRITE_SINGLE_COIL > 0
    case MODBUS_FUNCTION_WRITE_SINGLE_COIL:
        return modbus_server__handle_write_single_coil();
#endif

#if defined(MODBUS_SERVER__HANDLE_WRITE_REGISTER) && MODBUS_SERVER__HANDLE_WRITE_REGISTER > 0
    case MODBUS_FUNCTION_WRITE_REGISTER:
        return modbus_server__handle_write_register();
#endif

    default:
        return MODBUS_EXCEPTION__ILLEGAL_FUNCTION;
    }
}


bool modbus_rtu_driver__on_frame_received(void) {
    const uint16_t length = buffer__limit__get();
    if (length < MODBUS_FRAME_SIZE_MIN || crc16(0xFFFF, buffer__data, length)) return false;

    modbus_server__process_frame();

    // finish response by computing CRC; buffer__limit will point to the end of frame
    buffer__put_u16(crc16(0xFFFF, buffer__data, buffer__limit__get()));

    // send response
    buffer__rewind();
    return true;
}
