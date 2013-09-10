// =============================================================================
// MODBUS server.
// =============================================================================

#include "modbus_server.h"
#include "buffer.h"
#include "modbus_rtu_driver__usart_rx.h"
#include "modbus_rtu_driver__usart_tx.h"
#include "util/crc16_table2x256.h"
#include "modbus.h"


// helper module bindings
// -----------------------------------------------------------------------------

volatile bool modbus_server__frame_received;


/**
 * Called when data received would overflow the buffer.
 */
void modbus_rtu_driver__usart_rx__on_buffer_overflow(void) {
    modbus_rtu_driver__usart_rx__disable();
    buffer__clear();  
}

void modbus_rtu_driver__delay_timer__on_t15_expired(void) {
    modbus_rtu_driver__usart_rx__disable();
}

/**
 * Called when data are received when they should not be.
 */
void modbus_rtu_driver__usart_rx__on_unexpected_data(void) {
    // empty frame will be received and dropped.
    // transmittion will be aborted, if ongoing.
    buffer__clear();
}


void modbus_rtu_driver__delay_timer__on_t35_expired(void) {
    modbus_rtu_driver__delay_timer__stop();
    modbus_server__frame_received = true;
}

void modbus_rtu_driver__usart_tx__on_frame_sent(void) {
    modbus_rtu_driver__usart_tx__disable();    
    modbus_rtu_driver__usart_rx__enable();
}


// modbus server
// -----------------------------------------------------------------------------

void modbus_server__init(void) {
    buffer__init();
    modbus_rtu_driver__delay_timer__init();
}

void modbus_server__start(void) {
    modbus_rtu_driver__usart_rx__enable();
    modbus_rtu_driver__delay_timer__start();
}


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


bool modbus_server__run(void) {
    if (!modbus_server__frame_received) return false;

    modbus_server__frame_received = false;
    const uint16_t length = buffer__limit__get();
    if (length >= MODBUS_FRAME_SIZE_MIN && crc16(0xFFFF, buffer__data, length) == 0) {
        modbus_server__process_frame();

        // finish response by computing CRC; buffer__limit will point to the end of frame
        buffer__put_u16(crc16(0xFFFF, buffer__data, buffer__limit__get()));

        // send response
        buffer__rewind();
        modbus_rtu_driver__usart_tx__enable();
    }
    else {
        modbus_rtu_driver__usart_rx__enable();
    }
    return true;
}
