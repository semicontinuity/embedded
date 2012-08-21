// =============================================================================
// CAN Networking service.
//
// The following constants must be defined:
//
// - CANP_DEVICE_NET	network id
// - CANP_DEVICE_ADDR	address in the network
// ...
// =============================================================================

#ifndef __CAN_H
#define __CAN_H

#include "can_selector.h"

#include "cpu/avr/drivers/net/can/mcp251x/registers.h"
#include "cpu/avr/drivers/net/can/mcp251x/opmodes.h"
#include "cpu/avr/drivers/net/can/mcp251x/struct.h"
#include "cpu/avr/drivers/net/can/mcp251x/instructions.h"
#include "cpu/avr/drivers/net/can/mcp251x/operations.h"

#include "buttons_scanner.h"


// RX Filters 0-2
extern mcp251x_message_id can__rxf0_2[3] PROGMEM;

// RX Filters 3-5
extern mcp251x_message_id can__rxf3_5[3] PROGMEM;

// RX Masks 0 and 1
extern mcp251x_message_id can__rxm0_1[2] PROGMEM;

// TX Buffer 2 Header
// Used exclusively for sending notifications from buttons.
extern mcp251x_frame_header can__txb2_h PROGMEM;


/**
 * Performs MCP251x controller configuration.
 * Uploads all the data that remains constant during the operation of the device
 * - Masks
 * - Filters
 * - TX Buffer 2, used to send buttons status notifications.
 */ 
inline static void can__init(void) {
    can_selector__run(mcp251x_write_bytes_progmem((uint8_t* PROGMEM)&can__rxf0_2, MCP251X_REGISTER_RXF0SIDH, sizeof(can__rxf0_2)));
    can_selector__run(mcp251x_write_bytes_progmem((uint8_t* PROGMEM)&can__rxf3_5, MCP251X_REGISTER_RXF3SIDH, sizeof(can__rxf3_5)));
    can_selector__run(mcp251x_write_bytes_progmem((uint8_t* PROGMEM)&can__rxm0_1, MCP251X_REGISTER_RXM0SIDH, sizeof(can__rxm0_1)));

    // Note: could implement mcp2515_load_tx_buffer_progmem
    can_selector__run(mcp251x_write_bytes_progmem((uint8_t* PROGMEM)&can__txb2_h, MCP251X_REGISTER_TXB2SIDH, sizeof(can__txb2_h)));
}


inline static void can__start(void) {
    can_selector__run(mcp251x_write_byte(MCP251X_REGISTER_CANCTRL, MCP251X_OPMODE_NORMAL));
}


/**
 * Processes pending notifications that are sent using TX Buffer 2.
 */ 
inline static void can__txb2__run(void) {
    if (buttons_scanner__pins_changed != 0) {
        // It is assumed that time between pin changes (at least one system tick) is enough to send notification.
        // If for some reason it was not enough (most likely network problem), abort the transmission in progress.
        // TODO: abort possible ongoing transmission.
        can_selector__run(mcp2515_load_tx_buffer(buttons_scanner__status, MCP251X_INSTRUCTION_LOAD_BUFFER_2_D0, sizeof(buttons_scanner__status)));
        can_selector__run(mcp2515_request_to_send(MCP251X_INSTRUCTION_REQUEST_TO_SEND | MCP251X_INSTRUCTION_REQUEST_TO_SEND_B2));
    }
}

/**
 * Processes pending notifications.
 */ 
inline static void can__run(void) {
    can__txb2__run();
}


#endif