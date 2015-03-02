// =============================================================================================================
// Modbus RTU driver.
//
// States:
//
// +-> RX -> RX_REJECT -> FRAME_RECEIVED -> FRAME_PROCESSING -> TX ->-+
// |                                                   |              |
// +------------------------<--------------------------+              |
// +------------------------<-----------------------------------------+
//
// =============================================================================================================

#include "modbus_rtu_driver.h"
#include "buffer.h"
#include "modbus_rtu_driver__delay_timer.h"
#include "modbus_rtu_driver__dir_control.h"
#include "modbus_rtu_driver__usart_rx.h"
#include "modbus_rtu_driver__usart_tx.h"
#include "cpu/avr/usart0.h"


// Modbus RTU driver - frame_received flag
// -----------------------------------------------------------------------------

/**
 * Indicates that a frame has been received.
 */
volatile bool modbus_rtu_driver__frame_received;

bool modbus_rtu_driver__frame_received__get(void) {
    return modbus_rtu_driver__frame_received;
}

void modbus_rtu_driver__frame_received__set(const bool value) {
    modbus_rtu_driver__frame_received = value;
}

// State transitions
// -----------------------------------------------------------------------------

void modbus_rtu_driver__invalidate_frame(void) {
    buffer__clear();	// mark the frame as invalid
}

void modbus_rtu_driver__to_RX_REJECT(void) {
    modbus_rtu_driver__usart_rx__disable();     // any received data from now on are unexpected - must be in 3.5T inter-frame timeout.
}

void modbus_rtu_driver__RX_REJECT_to_FRAME_RECEIVED(void) {
    modbus_rtu_driver__delay_timer__stop();
    modbus_rtu_driver__frame_received__set(true);    
}

void modbus_rtu_driver__FRAME_RECEIVED_to_FRAME_PROCESSING(void) {
    modbus_rtu_driver__frame_received__set(false);    
}

void modbus_rtu_driver__FRAME_PROCESSING_to_TX(void) {
    modbus_rtu_driver__dir_control__tx();
    modbus_rtu_driver__usart_tx__signal();
}

void modbus_rtu_driver__TX_to_RX(void) {
    // NB: transmission is immediate, most likely, should receive only after 3.5T timeout.
    buffer__clear();    
    modbus_rtu_driver__dir_control__rx();
    modbus_rtu_driver__usart_rx__enable();      // indicate that any received data from now on are expected
}

void modbus_rtu_driver__FRAME_PROCESSING_to_RX(void) {
    modbus_rtu_driver__usart_rx__enable();
}


// Modbus RTU driver - helper module bindings (callback implementations)
// -----------------------------------------------------------------------------

/**
 * Switches from TX mode to RX mode.
 * @thread usart0__tx__complete
 */
void modbus_rtu_driver__usart_tx__on_frame_sent(void) {
    modbus_rtu_driver__TX_to_RX();
    modbus_rtu_driver__on_frame_sent(); // called in any case, even if there was a protocol error and transmission was aborted
}

/**
 * Called when data received would overflow the buffer.
 */
void modbus_rtu_driver__usart_rx__on_buffer_overflow(void) {
    modbus_rtu_driver__on_buffer_overflow();
    modbus_rtu_driver__invalidate_frame();
    modbus_rtu_driver__to_RX_REJECT();
}

void modbus_rtu_driver__delay_timer__on_t15_expired(void) {
    modbus_rtu_driver__to_RX_REJECT();
}

/**
 * Called when data are received when they should not be.
 */
void modbus_rtu_driver__usart_rx__on_unexpected_data(void) {
    // If unexpected character is received in FRAME_RECEIVED state (received frame is not yet handled),
    // corrupt the received frame by setting its size to 0 (could be double-checked at the end of frame handler).

    // If unexpected character is received in TX state (received character when the response is not yet fully transmitted),
    // corrupt the received frame by setting its size to 0 (will abort transmission).

    modbus_rtu_driver__on_protocol_error();
    modbus_rtu_driver__invalidate_frame();
}


void modbus_rtu_driver__delay_timer__on_t35_expired(void) {
    modbus_rtu_driver__RX_REJECT_to_FRAME_RECEIVED();
}



// Modbus RTU driver
// -----------------------------------------------------------------------------

void modbus_rtu_driver__init(void) {
    usart0__rate__set(USART0__BAUD_RATE);
    buffer__init();
    modbus_rtu_driver__delay_timer__init();
    modbus_rtu_driver__dir_control__init();
}

void modbus_rtu_driver__start(void) {
    modbus_rtu_driver__delay_timer__start();
    modbus_rtu_driver__usart_rx__start();
    modbus_rtu_driver__usart_tx__start();
}


void modbus_rtu_driver__stop(void) {
    modbus_rtu_driver__delay_timer__stop();
    modbus_rtu_driver__usart_tx__stop();
    modbus_rtu_driver__usart_rx__stop();
}


void modbus_rtu_driver__handle_received_frame(void) {
    modbus_rtu_driver__FRAME_RECEIVED_to_FRAME_PROCESSING();
    if (modbus_rtu_driver__on_frame_received()) {
        // Response must be sent
        modbus_rtu_driver__FRAME_PROCESSING_to_TX();
    }
    else {
        // No response must be sent, ok to receive next frame
        modbus_rtu_driver__FRAME_PROCESSING_to_RX();
    }
}


bool modbus_rtu_driver__is_runnable(void) {
    return modbus_rtu_driver__frame_received__get();
}


/**
 * Called periodically to run MODBUS RTU communication.
 * Must be called only if the thread is runnable (i.e. once for every received frame).
 */ 
void modbus_rtu_driver__run(void) {
    modbus_rtu_driver__handle_received_frame();
}
