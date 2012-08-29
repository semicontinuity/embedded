#ifndef __COMM_SERVICE__MOTOR_CONTOLLER_H
#define __COMM_SERVICE__MOTOR_CONTOLLER_H

#include "comm_service.h"
#include "motor_controller.h"
#include CAN_H


inline static void comm_service__motor_controller__motor_mode__handle(void) {
    if (comm_service__buffer.header.dlc & (1 << MCP251X_RTR)) {
        // Handle GET request
        comm_service__send_response(CANP_REPORT__MOTOR_CONTROLLER__MOTOR_MODE, sizeof(motor_controller__motor_mode), (const uint8_t*)&motor_controller__motor_mode);
    }
    else {
        // Handle PUT request
        motor_controller__motor_mode__set_from_raw_ptr(&comm_service__buffer.data);
    }
}

inline static void comm_service__motor_controller__motor_mode__broadcast(void) {
    // It is assumed that the time between motor mode changes (at least one system tick) is enough to send notification.
    // If for some reason it was not enough (most likely network problem), abort the transmission in progress.
    can__txb1__load_report(CANP_REPORT__MOTOR_CONTROLLER__MOTOR_MODE, sizeof(motor_controller__motor_mode), (const uint8_t*)&motor_controller__motor_mode);
    can__txb1__request_to_send();
}


inline static void comm_service__motor_controller__control__handle(void) {
    if (comm_service__buffer.header.dlc & (1 << MCP251X_RTR)) {
        // Handle GET request
        comm_service__send_response(CANP_REPORT__MOTOR_CONTROLLER__CONTROL, sizeof(motor_controller__control), (const uint8_t*)&motor_controller__control);
    }
    else {
        // Handle PUT request
        motor_controller__control__set_from_raw_ptr(&comm_service__buffer.data);
    }
}


inline static void comm_service__motor_controller__status__handle(void) {
    if (comm_service__buffer.header.dlc & (1 << MCP251X_RTR)) {
        // Handle GET request
        comm_service__send_response(CANP_REPORT__MOTOR_CONTROLLER__STATUS, sizeof(motor_controller__status), (const uint8_t*)&motor_controller__status);
    }
    // If DATA frame was received, ignore (perhaps, log as malformed request)
}

inline static void comm_service__motor_controller__status__broadcast(void) {
    // It is assumed that the time between motor controller status changes (at least one system tick) is enough to send notification.
    // If for some reason it was not enough (most likely network problem), abort the transmission in progress.
    can__txb1__load_report(CANP_REPORT__MOTOR_CONTROLLER__STATUS, sizeof(motor_controller__status), (const uint8_t*)&motor_controller__status);
    can__txb1__request_to_send();
}

#endif