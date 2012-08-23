// =============================================================================
// CAN service.
//
// Handles CAN communications.
// Services incoming requests.
//
// The device is designed for the system with one super-node ("master").
// The master is the only device that can send messages to the node.
//
// If master has sent GET request to the node,
// it should not send other GET requests to the node until it receives response.
// If the responce is not received in certain time,
// the master assumes that the node is malfunctioning.
// =============================================================================

#include "can_service.h"
#include "can_selector.h"

#include "cpu/avr/drivers/net/can/mcp251x/bitdefs.h"
#include "cpu/avr/drivers/net/can/mcp251x/instructions.h"
#include "cpu/avr/drivers/net/can/mcp251x/registers.h"
#include "cpu/avr/drivers/net/can/mcp251x/operations.h"
#include "cpu/avr/drivers/net/can/mcp251x/struct.h"
#include "cpu/avr/drivers/net/can/mcp251x/interrupt-codes.h"

#include "cpu/avr/drivers/net/can/mcp251x/canp.h"


#include "motor_controller.h"

#include <stdint.h>
#include <avr/interrupt.h>


static volatile mcp251x_message_buffer buffer;


void can_service__broadcast_buttons_status(void) {
    // It is assumed that the time between pin changes (at least one system tick) is enough to send notification.
    // If for some reason it was not enough (most likely network problem), abort the transmission in progress.
    can__txb2__load_data(buttons_scanner__status, sizeof(buttons_scanner__status));
    can__txb2__request_to_send();
}

void can_service__broadcast_motor_status(void) {
    // It is assumed that the time between motor mode changes (at least one system tick) is enough to send notification.
    // If for some reason it was not enough (most likely network problem), abort the transmission in progress.
    can__txb1__load_report(CANP_REPORT__MOTOR__STATUS, sizeof(motor__mode), &motor__mode);
    can__txb1__request_to_send();
}

void can_service__broadcast_motor_controller_status(void) {
    // It is assumed that the time between motor controller status changes (at least one system tick) is enough to send notification.
    // If for some reason it was not enough (most likely network problem), abort the transmission in progress.
    can__txb1__load_report(CANP_REPORT__MOTOR_CONTROLLER__STATUS, sizeof(motor_controller__status), motor_controller__status);
    can__txb1__request_to_send();
}


static inline void can_service__handle_motor_controller_control(void) {
    if (buffer.header.dlc & (1 << MCP251X_RTR)) {
        // Received GET request for motor_controller_control.

        // Convert buffer to response.        
        buffer.header.dlc &= 0x0F; // Leave only data length in dlc field
        can__txb0__load_buffer((uint8_t*)&buffer, CANP_BASIC_HEADER_SIZE);
        can__txb0__load_report(CANP_REPORT__MOTOR_CONTROLLER__CONTROL, sizeof(motor_controller__control), motor_controller__control);
        can__txb0__request_to_send();
    }
    else {
        // Received PUT request for motor_controller_control.
        motor_controller__final_position__set(buffer.data[0]);
    }
}


static inline void can_service__handle_rx(void) {
    uint8_t status;
    can_selector__run(status = mcp2515_rx_status());

    // For remote frames, read just the header.
    // For data frames, read the header + all 8 bytes of payload, even though DLC can be less than 8.
    uint8_t count = status & MCP251X__RX_STATUS__TYPE__REMOTE ? sizeof(buffer.header) : sizeof(buffer);
    uint8_t instruction = status & MCP251X__RX_STATUS__BUFFER__0 ? MCP251X_REGISTER_RXB0SIDH : MCP251X_REGISTER_RXB1SIDH;

    can_selector__run(mcp2515_read_rx_buffer((uint8_t*)&buffer.header, instruction, count));

    switch (status & MCP251X__RX_STATUS__FILTER__MASK) {
    case CANP_FILTER__MOTOR_CONTROLLER__CONTROL:
        can_service__handle_motor_controller_control();
        break;
    }
}


/**
 *  Handler for the interrupt from MCP2515 CAN controller (falling edge).
 */
ISR(INT1_vect) {
    // interrupt flag for INT1 cleared automatically
    // The only source of interrupt is from RX buffer 0.
    // Clears interrupts.
    can_service__handle_rx();
}
