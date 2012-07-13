#ifndef __CAN_SERVICE_H
#define __CAN_SERVICE_H

#include "device.h"
#include <avr/io.h>
#include "cpu/avr/gpio.h"
#include "cpu/avr/drivers/net/can/mcp251x/bitdefs.h"
#include "cpu/avr/drivers/net/can/mcp251x/registers.h"
#include "cpu/avr/drivers/net/can/mcp251x/operations.h"


inline void can_service__init(void) {
    // external interrupt from INT1 pin, falling edge
    MCUCR = _BV(ISC11);
}


inline void can_service__start(void) {
    GICR  = _BV(INT1);	// enable external interrupt from INT1 pin
    STROBED_LOW (SS, mcp251x_write_byte (MCP251X_REGISTER_CANINTE, _BV(MCP251X_RX0IE)));
}

#endif