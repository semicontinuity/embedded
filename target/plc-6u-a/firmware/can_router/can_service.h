#ifndef __CAN_SERVICE_H
#define __CAN_SERVICE_H

#include <avr/io.h>
#include "cpu/avr/drivers/net/can/mcp251x/bitdefs.h"
#include "cpu/avr/drivers/net/can/mcp251x/registers.h"
#include "cpu/avr/drivers/net/can/mcp251x/operations.h"


inline void can_service__init(void) {
    // INT0 is on PD2, configure internal pull-up.
    PORTD |= _BV(2);    
    // interrupt on INT0 pin falling edge
    EICRA = (1<<ISC01);
}


inline void can_service__start(void) {
    // Enable interrupt from INT0
    EIMSK |= (1<<INT0);
    // Enable RX0 interrupt in the CAN controller
    MCP251X_SPI_COMM(mcp251x_write_byte (MCP251X_REGISTER_CANINTE, _BV(MCP251X_RX0IE)));
}

#endif // __CAN_SERVICE_H