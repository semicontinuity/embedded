// The only interrupt signal is at PC3 (PCINT11)

#ifndef __CAN_SERVICE_H
#define __CAN_SERVICE_H

#include <avr/io.h>
#include "drivers/out/mcp251x_select.h"
#include "cpu/avr/drivers/net/can/mcp251x/bitdefs.h"
#include "cpu/avr/drivers/net/can/mcp251x/registers.h"
#include "cpu/avr/drivers/net/can/mcp251x/operations.h"


#define CAN_CONTROLLER_INTERRUPT ISR(PCINT1_vect, ISR_NAKED)


inline void can_service__init(void) {
    PCMSK1 |= _BV(PCINT11);// any change on PC3
}


inline void can_service__start(void) {
    PCICR |= _BV(PCIE1);

    // Enable RX0 interrupt in the CAN controller
    mcp251x_select__run(mcp251x_write_one_byte(MCP251X_REGISTER_CANINTE, _BV(MCP251X_RX0IE)));
}

#endif // __CAN_SERVICE_H