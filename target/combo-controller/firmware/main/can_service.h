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

#include "cpu/avr/int0.h"

#include "can.h"
#include "can_selector.h"

#include "cpu/avr/drivers/net/can/mcp251x/registers.h"
#include "cpu/avr/drivers/net/can/mcp251x/operations.h"
#include "cpu/avr/drivers/net/can/mcp251x/conf.h"

/**
 * Implements the function from comm_service__rx.
 */ 
inline static void comm_service__rx__init(void) {
    int0__init();
    can__init();
}


/**
 * Implements the function from comm_service__rx.
 */ 
inline static void comm_service__rx__start(void) {
    int0__start();
    can__start();

    // TODO: abstract
    can_selector__run(mcp251x_write_one_byte(MCP251X_REGISTER_CANINTE, _BV(MCP251X_RX0IE)|_BV(MCP251X_RX1IE)|_BV(MCP251X_TX1IE)|_BV(MCP251X_TX2IE)));
}

#include "kernel__rx__handler.h"
#include "kernel__tx__handler.h"

#endif