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

#include "buttons_scanner.h"
#include "motor_controller.h"

#include <stdint.h>
#include <avr/interrupt.h>


static volatile mcp251x_message_buffer buffer;


static inline void can_service__handle__motor_controller__motor_mode(void) {
    if (buffer.header.dlc & (1 << MCP251X_RTR)) {
        // Handle GET request
        // Convert buffer to response.        
        buffer.header.dlc &= 0x0F; // Leave only data length in dlc field
        can__txb0__load_buffer((uint8_t*)&buffer, CANP_BASIC_HEADER_SIZE);
        can__txb0__load_report(CANP_REPORT__MOTOR_CONTROLLER__MOTOR_MODE, sizeof(motor_controller__motor_mode), (const uint8_t*)&motor_controller__motor_mode);
        can__txb0__request_to_send();
    }
    else {
        // Handle PUT request
        motor_controller__motor_mode__set_from_raw_ptr(&buffer.data);
    }
}


static inline void can_service__handle_motor_controller_control(void) {
    if (buffer.header.dlc & (1 << MCP251X_RTR)) {
        // Handle GET request
        // Convert buffer to response.        
        buffer.header.dlc &= 0x0F; // Leave only data length in dlc field
        can__txb0__load_buffer((uint8_t*)&buffer, CANP_BASIC_HEADER_SIZE);
        can__txb0__load_report(CANP_REPORT__MOTOR_CONTROLLER__CONTROL, sizeof(motor_controller__control), (const uint8_t*)&motor_controller__control);
        can__txb0__request_to_send();
    }
    else {
        // Handle PUT request
        motor_controller__control__set_from_raw_ptr(&buffer.data);
    }
}


static inline void can_service__handle_motor_controller_status(void) {
    if (buffer.header.dlc & (1 << MCP251X_RTR)) {
        // Handle GET request
        // Convert buffer to response.        
        buffer.header.dlc &= 0x0F; // Leave only data length in dlc field
        can__txb0__load_buffer((uint8_t*)&buffer, CANP_BASIC_HEADER_SIZE);
        can__txb0__load_report(CANP_REPORT__MOTOR_CONTROLLER__STATUS, sizeof(motor_controller__status), (const uint8_t*)&motor_controller__status);
        can__txb0__request_to_send();
    }
    // If DATA frame was received, ignore (perhaps, log as malformed request)
}


static inline void can_service__handle_buttons_scanner_status(void) {
    if (buffer.header.dlc & (1 << MCP251X_RTR)) {
        // Handle GET request
        // Convert buffer to response.        
        buffer.header.dlc &= 0x0F; // Leave only data length in dlc field
        can__txb0__load_buffer((uint8_t*)&buffer, CANP_BASIC_HEADER_SIZE);
        can__txb0__load_report(CANP_REPORT__BUTTONS_SCANNER__STATUS, sizeof(buttons_scanner__status), (const uint8_t*)&buttons_scanner__status);
        can__txb0__request_to_send();
    }
    // If DATA frame was received, ignore (perhaps, log as malformed request)
}


static inline void can_service__handle_rx(void) {
    switch (can__read_frame((uint8_t*)&buffer)) {
    case CANP_FILTER__MOTOR_CONTROLLER__MOTOR_MODE:
        can_service__handle__motor_controller__motor_mode();
        break;
    case CANP_FILTER__MOTOR_CONTROLLER__CONTROL:
        can_service__handle_motor_controller_control();
        break;
    case CANP_FILTER__MOTOR_CONTROLLER__STATUS:
        can_service__handle_motor_controller_status();
        break;
    case CANP_FILTER__BUTTONS_SCANNER__STATUS:
        can_service__handle_buttons_scanner_status();
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
