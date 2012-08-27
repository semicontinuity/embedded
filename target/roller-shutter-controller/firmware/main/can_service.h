// =============================================================================
// CAN service.
// Handles CAN communications (services incoming requests).
// Implements comm_service.
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

#include "comm_service.h"

#include "can.h"
#include "can_selector.h"

#include "cpu/avr/drivers/net/can/mcp251x/bitdefs.h"
#include "cpu/avr/drivers/net/can/mcp251x/registers.h"
#include "cpu/avr/drivers/net/can/mcp251x/operations.h"
#include "cpu/avr/drivers/net/can/mcp251x/canp.h"


#include "buttons_scanner.h"
#include "motor_controller.h"


inline static void can_service__start(void) {
    can_selector__run(mcp251x_write_one_byte(MCP251X_REGISTER_CANINTE, _BV(MCP251X_RX0IE)|_BV(MCP251X_RX1IE)));
}


inline static void can_service__broadcast_buttons_status(void) {
    // It is assumed that the time between pin changes (at least one system tick) is enough to send notification.
    // If for some reason it was not enough (most likely network problem), abort the transmission in progress.
    can__txb2__load_data((const uint8_t*)&buttons_scanner__status, sizeof(buttons_scanner__status));
    can__txb2__request_to_send();
}

inline static void can_service__broadcast_motor_controller__motor_mode(void) {
    // It is assumed that the time between motor mode changes (at least one system tick) is enough to send notification.
    // If for some reason it was not enough (most likely network problem), abort the transmission in progress.
    can__txb1__load_report(CANP_REPORT__MOTOR_CONTROLLER__MOTOR_MODE, sizeof(motor_controller__motor_mode), (const uint8_t*)&motor_controller__motor_mode);
    can__txb1__request_to_send();
}

inline static void can_service__broadcast_motor_controller_status(void) {
    // It is assumed that the time between motor controller status changes (at least one system tick) is enough to send notification.
    // If for some reason it was not enough (most likely network problem), abort the transmission in progress.
    can__txb1__load_report(CANP_REPORT__MOTOR_CONTROLLER__STATUS, sizeof(motor_controller__status), (const uint8_t*)&motor_controller__status);
    can__txb1__request_to_send();
}


/**
 *  Handler for the interrupt from MCP2515 CAN controller (falling edge).
 */
static inline void can_service__run(void) {
    // Interrupt flag for INT1 cleared automatically when RX buffer is read.
    comm_service__handle_rx(can__read_frame((uint8_t*)&comm_service__buffer));
}


#endif