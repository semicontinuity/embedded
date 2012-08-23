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
#include "motor.h"
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


void can_service__broadcast_buttons_status(void);

void can_service__broadcast_motor_status(void);

void can_service__broadcast_motor_controller_status(void);


#endif