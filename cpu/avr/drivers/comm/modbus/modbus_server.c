// =============================================================================
// MODBUS server.
// =============================================================================

#include "cpu/avr/drivers/comm/modbus/modbus_server.h"
#include "cpu/avr/drivers/comm/modbus/buffer.h"
#include "cpu/avr/drivers/comm/modbus/modbus_rtu_driver.h"
#include "util/crc16_table2x256.h"


#if defined(MODBUS_SERVER__HANDLE_READ_COILS) && MODBUS_SERVER__HANDLE_READ_COILS > 0
/**
 * Handle reading of coils.
 */
modbus_exception modbus_server__handle_read_coils(void) {
    __asm__ __volatile__( "modbus_server__handle_read_coils:");
    const uint16_t length = buffer__limit__get();
    if (length != MODBUS_FRAME_SIZE_MIN + MODBUS_FUNCTION__READ_COILS__PAYLOAD_SIZE)
        return MODBUS_EXCEPTION__ILLEGAL_DATA_VALUE;

    buffer__sync(); // will write to the beginning of the payload section

    uint16_t address = buffer__get_u16();
    uint16_t count = buffer__get_u16();

    if (address != MODBUS_SERVER__COIL_ADDRESSES_START || count != MODBUS_SERVER__COIL_COUNT)
        return MODBUS_EXCEPTION__ILLEGAL_DATA_ADDRESS;


    buffer__put_u8((uint8_t) ((MODBUS_SERVER__COIL_COUNT + 7) >> 3) ); // byte count; the rest of the response is written by the handler
    return modbus_server__read_coils();
}
#endif


#if defined(MODBUS_SERVER__HANDLE_READ_HOLDING_REGISTERS) && MODBUS_SERVER__HANDLE_READ_HOLDING_REGISTERS > 0
/**
 * Handle reading of holding registers.
 */
modbus_exception modbus_server__handle_read_holding_registers(void) {
    __asm__ __volatile__( "modbus_server__handle_read_holding_registers:");
    const uint16_t length = buffer__limit__get();
    if (length != MODBUS_FRAME_SIZE_MIN + MODBUS_FUNCTION__READ_HOLDING_REGISTERS__PAYLOAD_SIZE)
        return MODBUS_EXCEPTION__ILLEGAL_DATA_VALUE;

    buffer__sync(); // will write to the beginning of the payload section

    uint16_t register_address = buffer__get_u16();
    uint16_t register_count = buffer__get_u16();

    if (register_count == 0 || register_count > MODBUS_FUNCTION__READ_HOLDING_REGISTERS__MAX_COUNT)
        return MODBUS_EXCEPTION__ILLEGAL_DATA_VALUE;

    if (register_address < MODBUS_SERVER__HOLDING_REGISTERS_START
        || register_address + register_count > MODBUS_SERVER__HOLDING_REGISTERS_START + MODBUS_SERVER__HOLDING_REGISTERS_COUNT)
        return MODBUS_EXCEPTION__ILLEGAL_DATA_ADDRESS;


    buffer__put_u8((uint8_t) register_count << 1); // byte count; the rest of the response is written by the handler
    return modbus_server__read_holding_registers(register_address, register_count);
}
#endif


#if defined(MODBUS_SERVER__HANDLE_READ_INPUT_REGISTERS) && MODBUS_SERVER__HANDLE_READ_INPUT_REGISTERS > 0
/**
 * Handle reading of input registers.
 */
modbus_exception modbus_server__handle_read_input_registers(void) {
    __asm__ __volatile__( "modbus_server__handle_read_input_registers:");
    const uint16_t length = buffer__limit__get();
    if (length != MODBUS_FRAME_SIZE_MIN + MODBUS_FUNCTION__READ_INPUT_REGISTERS__PAYLOAD_SIZE)
        return MODBUS_EXCEPTION__ILLEGAL_DATA_VALUE;

    buffer__sync(); // will write to the beginning of the payload section

    uint16_t register_address = buffer__get_u16();
    uint16_t register_count = buffer__get_u16();

    if (register_count == 0 || register_count > MODBUS_FUNCTION__READ_INPUT_REGISTERS__MAX_COUNT)
        return MODBUS_EXCEPTION__ILLEGAL_DATA_VALUE;

    if (register_address < MODBUS_SERVER__INPUT_REGISTERS_START
        || register_address + register_count > MODBUS_SERVER__INPUT_REGISTERS_START + MODBUS_SERVER__INPUT_REGISTERS_COUNT)
        return MODBUS_EXCEPTION__ILLEGAL_DATA_ADDRESS;


    buffer__put_u8((uint8_t) register_count << 1); // byte count; the rest of the response is written by the handler
    return modbus_server__read_input_registers(register_address, register_count);
}
#endif


#if defined(MODBUS_SERVER__HANDLE_WRITE_SINGLE_COIL) && MODBUS_SERVER__HANDLE_WRITE_SINGLE_COIL > 0
/**
 * Handle writing of single coil.
 */
modbus_exception modbus_server__handle_write_single_coil(void) {
    __asm__ __volatile__( "modbus_server__handle_write_single_coil:");
    const uint16_t length = buffer__limit__get();
    if (length != MODBUS_FRAME_SIZE_MIN + MODBUS_FUNCTION__WRITE_SINGLE_COIL__PAYLOAD_SIZE)
        return MODBUS_EXCEPTION__ILLEGAL_DATA_VALUE;

    uint16_t address = buffer__get_u16();
    uint16_t value = buffer__get_u16();

    uint16_t value_l = (uint8_t) value;
    if (value_l != 0) return MODBUS_EXCEPTION__ILLEGAL_DATA_VALUE;
    uint8_t value_h = (uint8_t) (value >> 8);
    if (value_h > 0 && value_h < 0xFF) return MODBUS_EXCEPTION__ILLEGAL_DATA_VALUE;

    if (address < MODBUS_SERVER__COIL_ADDRESSES_START
        || address >= MODBUS_SERVER__COIL_ADDRESSES_START + MODBUS_SERVER__COIL_COUNT)
        return MODBUS_EXCEPTION__ILLEGAL_DATA_ADDRESS;

    buffer__sync();    // will return the same data as arrived in the request (echo)
    return modbus_server__write_single_coil(address, value_h);
}
#endif


#if defined(MODBUS_SERVER__HANDLE_WRITE_REGISTER) && MODBUS_SERVER__HANDLE_WRITE_REGISTER > 0
/**
 * Handle writing of holding register.
 */
modbus_exception modbus_server__handle_write_register(void) {
    __asm__ __volatile__( "modbus_server__handle_write_register:");
    const uint16_t length = buffer__limit__get();
    if (length != MODBUS_FRAME_SIZE_MIN + MODBUS_FUNCTION__WRITE_REGISTER__PAYLOAD_SIZE)
        return MODBUS_EXCEPTION__ILLEGAL_DATA_VALUE;

    uint16_t register_address = buffer__get_u16();
    uint16_t register_value = buffer__get_u16();

    if (register_address < MODBUS_SERVER__HOLDING_REGISTERS_START
        || register_address >= MODBUS_SERVER__HOLDING_REGISTERS_START + MODBUS_SERVER__HOLDING_REGISTERS_COUNT)
        return MODBUS_EXCEPTION__ILLEGAL_DATA_ADDRESS;

    buffer__sync();    // will return the same data as arrived in the request (echo)
    return modbus_server__write_holding_register(register_address, register_value);
}
#endif


modbus_exception modbus_server__process_frame(void) {
    const uint8_t function = buffer__get_u8();
    switch (function) {
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


/**
 * Invoked by the driver on every received frame
 * @return true if the response must be sent (placed to the same buffer)
 */
bool modbus_rtu_driver__on_frame_received(void) {
    __asm__ __volatile__( "modbus_rtu_driver__on_frame_received:");
    const uint16_t length = buffer__limit__get();
    if (length == 0) return false; // timeout expired, no data yet (ok)

    if (length >= MODBUS_FRAME_SIZE_MIN) {
        __asm__ __volatile__( "modbus_rtu_driver__on_frame_received__compute_request_crc:");
        uint16_t crc = crc16(0xFFFF, buffer__data, length);
        if (!crc) {
        __asm__ __volatile__( "modbus_rtu_driver__on_frame_received__handle_valid_frame:");
            modbus_server__on_valid_frame_received();
            buffer__rewind(); // start parsing frame
            uint8_t address = buffer__get_u8();
            if (address == MODBUS_SERVER__ADDRESS) {
                __asm__ __volatile__( "modbus_rtu_driver__on_frame_received__process_frame:");
                // handle request; buffer__limit will point to the end of response payload
                modbus_server__process_frame();

                // finish response by computing CRC; buffer__limit will point to the end of frame
                uint16_t crc = crc16(0xFFFF, buffer__data, buffer__limit__get());
                buffer__put_u8((uint8_t) (crc & 0xFF)); // low byte of CRC is sent first.
                buffer__put_u8((uint8_t) (crc >> 8));   // cannot use buffer__put_u16 that sends 16-bit values MSB first.

                buffer__rewind();
                return true; // indicate that response must be sent
            }
            else {
                buffer__rewind();
                return false;
            }
        }
    }
    __asm__ __volatile__( "modbus_rtu_driver__on_frame_received__handle_invalid_frame:");
    modbus_server__on_invalid_frame_received();
    return false;
}
