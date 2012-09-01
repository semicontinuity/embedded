// =============================================================================
// CAN service.
// Handles CAN communications (services incoming requests).
// Extends comm_service__rx.
//
// The device is designed for the system with one super-node ("master").
// The master is the only device that can send messages to the node.
//
// If master has sent GET request to the node,
// it should not send other GET requests to the node until it receives response.
// If the responce is not received in certain time,
// the master assumes that the node is malfunctioning.
// =============================================================================
#ifndef __CAN_SERVICE_H
#define __CAN_SERVICE_H

#include <avr/io.h>
#include <avr/interrupt.h>

#include "cpu/avr/int1.h"

#include "comm_service.h"
#include "comm_service__handler.h"

#include "can.h"
#include "can_selector.h"

#include "cpu/avr/drivers/net/can/mcp251x/bitdefs.h"
#include "cpu/avr/drivers/net/can/mcp251x/registers.h"
#include "cpu/avr/drivers/net/can/mcp251x/operations.h"
#include "cpu/avr/drivers/net/can/mcp251x/canp.h"
#include "cpu/avr/drivers/net/can/mcp251x/conf.h"


#include "buttons_scanner.h"
#include "motor_controller.h"


/**
 * Implements the function from comm_service__rx.
 */ 
inline static void comm_service__rx__init(void) {
    int1__init();
    can__init();
}


/**
 * Implements the function from comm_service__rx.
 */ 
inline static void comm_service__rx__start(void) {
    int1__start();
    can__start();

    can_selector__run(mcp251x_write_one_byte(MCP251X_REGISTER_CANINTE, _BV(MCP251X_RX0IE)|_BV(MCP251X_RX1IE)));
}


/**
 *  Handler for the interrupt from MCP2515 CAN controller (falling edge).
 */
static inline void can_service__rx__run(void) {
    // Interrupt flag for INT1 cleared automatically when RX buffer is read.
    comm_service__rx__put(can__read_frame((uint8_t*)&comm_service__packet));
}


#endif