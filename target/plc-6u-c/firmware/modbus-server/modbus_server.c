// =============================================================================
// MODBUS server.
// =============================================================================

#include "modbus_server.h"
#include "buffer.h"
#include "usart_rx.h"
#include "usart_tx.h"
#include "util/crc16_table2x256.h"
#include "modbus.h"


// helper module bindings
// -----------------------------------------------------------------------------

volatile bool modbus_server__frame_received;


void usart_rx__on_buffer_overflow(void) {
    usart_rx__disable();
    buffer__limit = buffer__data;
}

void delay_timer__on_t15_expired(void) {
    usart_rx__disable();
}

void usart_rx__on_unexpected_data(void) {
    // received frame will be dropped (size == 0).
    // transmittion will be aborted, if ongoing.
    buffer__limit = buffer__data;
}


void delay_timer__on_t35_expired(void) {
    delay_timer__stop();
    modbus_server__frame_received = true;
}

void usart_tx__on_frame_sent(void) {
    usart_tx__disable();    
    usart_rx__enable();
}


// modbus server
// -----------------------------------------------------------------------------

void modbus_server__init(void) {
    usart_rx__enable();
    delay_timer__start();
}


bool modbus_server__run(void) {
    if (!modbus_server__frame_received) return false;

    modbus_server__frame_received = false;
    const uint16_t length = buffer__limit - buffer__data;
    if (length >= MODBUS_FRAME_SIZE_MIN && crc16(0xFFFF, buffer__data, length) == 0) {
        // process frame
        // send response
        buffer__position = buffer__data;
        usart_tx__enable();
    }
    else {
        usart_rx__enable();
    }
    return true;
}
