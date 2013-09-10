// =============================================================================
// Modbus RTU driver.
// =============================================================================

#include "modbus_rtu_driver.h"
#include "buffer.h"
#include "modbus_rtu_driver__delay_timer.h"
#include "modbus_rtu_driver__usart_rx.h"
#include "modbus_rtu_driver__usart_tx.h"


// Modbus RTU driver - helper module bindings
// -----------------------------------------------------------------------------

volatile bool modbus_rtu_driver__frame_received;


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
    modbus_rtu_driver__frame_received = true;
}

void modbus_rtu_driver__usart_tx__on_frame_sent(void) {
    modbus_rtu_driver__usart_tx__disable();    
    modbus_rtu_driver__usart_rx__enable();
}


// Modbus RTU driver
// -----------------------------------------------------------------------------

void modbus_rtu_driver__init(void) {
    buffer__init();
    modbus_rtu_driver__delay_timer__init();
}

void modbus_rtu_driver__start(void) {
    modbus_rtu_driver__usart_rx__enable();
    modbus_rtu_driver__delay_timer__start();
}


bool modbus_rtu_driver__is_runnable(void) {
    return modbus_rtu_driver__frame_received;
}


/**
 * Called periodically to run MODBUS RTU communication.
 * Must be called only if the thread is runnable.
 */ 
void modbus_rtu_driver__run(void) {
    modbus_rtu_driver__frame_received = false;
    if (modbus_rtu_driver__on_frame_received()) {
        modbus_rtu_driver__usart_tx__enable();
    }
    else {
        modbus_rtu_driver__usart_rx__enable();
    }
}
