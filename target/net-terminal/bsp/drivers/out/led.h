// =============================================================================
// Driver for the LED.
// LED is connected to RX0BF pin of the MCP2515. RX1BF is free.
// =============================================================================

#ifndef __DRIVERS__OUT__LED_H
#define __DRIVERS__OUT__LED_H

#include "can_selector.h"
#include "cpu/avr/drivers/net/can/mcp251x/bitdefs.h.h"
#include "cpu/avr/drivers/net/can/mcp251x/operations.h"


inline void led__on(void) {
    can_selector__run(mcp251x_write_one_byte(MCP251X_REGISTER_BFPCTRL, (1<<MCP251X_B0BFS)|(1<<MCP251X_B0BFE)));
}


inline void led__off(void) { 
    can_selector__run(mcp251x_write_one_byte(MCP251X_REGISTER_BFPCTRL, 0));
}


#endif