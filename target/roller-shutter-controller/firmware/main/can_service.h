#ifndef __CAN_SERVICE_H
#define __CAN_SERVICE_H

#include <avr/io.h>
#include <avr/interrupt.h>

#include "can.h"
#include "can_selector.h"

#include "cpu/avr/drivers/net/can/mcp251x/bitdefs.h"
#include "cpu/avr/drivers/net/can/mcp251x/registers.h"
#include "cpu/avr/drivers/net/can/mcp251x/operations.h"

#include "buttons_scanner.h"
#include "motor_controller.h"


inline static void can_service__init(void) {
    // pullup?
    // external interrupt from INT1 pin, falling edge
    // interrupt on INT0 pin falling edge
    EICRA = (1<<ISC11);
}


inline static void can_service__start(void) {
    // Enable interrupt from INT0
    EIMSK |= (1<<INT1);
    can_selector__run(mcp251x_write_one_byte(MCP251X_REGISTER_CANINTE, _BV(MCP251X_RX0IE)));
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


#endif