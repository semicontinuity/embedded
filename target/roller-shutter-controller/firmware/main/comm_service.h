// =============================================================================
// Communications service.
//
// Services incoming requests.
// =============================================================================
#ifndef __COMM_SERVICE_H
#define __COMM_SERVICE_H

#include <avr/io.h>
#include <avr/interrupt.h>

#include "cpu/avr/drivers/net/can/mcp251x/bitdefs.h"
#include "cpu/avr/drivers/net/can/mcp251x/instructions.h"
#include "cpu/avr/drivers/net/can/mcp251x/registers.h"
#include "cpu/avr/drivers/net/can/mcp251x/operations.h"
#include "cpu/avr/drivers/net/can/mcp251x/canp.h"
#include "cpu/avr/drivers/net/can/mcp251x/struct.h"

#include "buttons_scanner.h"
#include "motor_controller.h"
#include CAN_H

extern volatile mcp251x_message_buffer comm_service__buffer;



void comm_service__send_response(const uint8_t report_id, const uint8_t count, const uint8_t* data);

#include "comm_service__admin_handler.h"




static inline void comm_service__handle__descriptor_memory(void) {
}


static inline void comm_service__handle__motor_controller__motor_mode(void) {
    if (comm_service__buffer.header.dlc & (1 << MCP251X_RTR)) {
        // Handle GET request
        comm_service__send_response(CANP_REPORT__MOTOR_CONTROLLER__MOTOR_MODE, sizeof(motor_controller__motor_mode), (const uint8_t*)&motor_controller__motor_mode);
    }
    else {
        // Handle PUT request
        motor_controller__motor_mode__set_from_raw_ptr(&comm_service__buffer.data);
    }
}


static inline void comm_service__handle_motor_controller_control(void) {
    if (comm_service__buffer.header.dlc & (1 << MCP251X_RTR)) {
        // Handle GET request
        comm_service__send_response(CANP_REPORT__MOTOR_CONTROLLER__CONTROL, sizeof(motor_controller__control), (const uint8_t*)&motor_controller__control);
    }
    else {
        // Handle PUT request
        motor_controller__control__set_from_raw_ptr(&comm_service__buffer.data);
    }
}


static inline void comm_service__handle_motor_controller_status(void) {
    if (comm_service__buffer.header.dlc & (1 << MCP251X_RTR)) {
        // Handle GET request
        comm_service__send_response(CANP_REPORT__MOTOR_CONTROLLER__STATUS, sizeof(motor_controller__status), (const uint8_t*)&motor_controller__status);
    }
    // If DATA frame was received, ignore (perhaps, log as malformed request)
}


static inline void comm_service__handle_buttons_scanner_status(void) {
    if (comm_service__buffer.header.dlc & (1 << MCP251X_RTR)) {
        // Handle GET request
        comm_service__send_response(CANP_REPORT__BUTTONS_SCANNER__STATUS, sizeof(buttons_scanner__status), (const uint8_t*)&buttons_scanner__status);
    }
    // If DATA frame was received, ignore (perhaps, log as malformed request)
}


static inline void comm_service__handle_rx(uint8_t filter) {
    switch (filter) {
    case CANP_FILTER__DESCRIPTOR_MEMORY:
        comm_service__handle__descriptor_memory();
        break;
    case CANP_FILTER__ADMIN:
        comm_service__handle__admin();
        break;
    case CANP_FILTER__USER:
    case CANP_FILTER__USER_MCAST:
        switch (CANP_SLOT_BITS(comm_service__buffer.header.id)) {
        case CANP_REPORT__MOTOR_CONTROLLER__MOTOR_MODE:
            comm_service__handle__motor_controller__motor_mode();
            break;
        case CANP_REPORT__MOTOR_CONTROLLER__CONTROL:
            comm_service__handle_motor_controller_control();
            break;
        case CANP_REPORT__MOTOR_CONTROLLER__STATUS:
            comm_service__handle_motor_controller_status();
            break;
        case CANP_REPORT__BUTTONS_SCANNER__STATUS:
            comm_service__handle_buttons_scanner_status();
            break;
        }
    }
}


inline static void comm_service__broadcast_buttons_status(void) {
    // It is assumed that the time between pin changes (at least one system tick) is enough to send notification.
    // If for some reason it was not enough (most likely network problem), abort the transmission in progress.
    can__txb2__load_data((const uint8_t*)&buttons_scanner__status, sizeof(buttons_scanner__status));
    can__txb2__request_to_send();
}

inline static void comm_service__broadcast_motor_controller__motor_mode(void) {
    // It is assumed that the time between motor mode changes (at least one system tick) is enough to send notification.
    // If for some reason it was not enough (most likely network problem), abort the transmission in progress.
    can__txb1__load_report(CANP_REPORT__MOTOR_CONTROLLER__MOTOR_MODE, sizeof(motor_controller__motor_mode), (const uint8_t*)&motor_controller__motor_mode);
    can__txb1__request_to_send();
}

inline static void comm_service__broadcast_motor_controller_status(void) {
    // It is assumed that the time between motor controller status changes (at least one system tick) is enough to send notification.
    // If for some reason it was not enough (most likely network problem), abort the transmission in progress.
    can__txb1__load_report(CANP_REPORT__MOTOR_CONTROLLER__STATUS, sizeof(motor_controller__status), (const uint8_t*)&motor_controller__status);
    can__txb1__request_to_send();
}


#endif