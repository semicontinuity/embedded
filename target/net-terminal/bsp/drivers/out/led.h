// =============================================================================
// Driver for the LED.
// LED is connected to RX0BF pin of the MCP2515. RX1BF is free.
// =============================================================================

#ifndef __DRIVERS__OUT__LED_H
#define __DRIVERS__OUT__LED_H

#include "drivers/out/mcp251x_select.h"
#include "cpu/avr/drivers/net/can/mcp251x/bitdefs.h"
#include "cpu/avr/drivers/net/can/mcp251x/operations.h"
#include "cpu/avr/drivers/net/can/mcp251x/registers.h"


INLINE void led__on(void) {
    mcp251x__write(MCP251X_REGISTER_BFPCTRL, (1<<MCP251X_B0BFS)|(1<<MCP251X_B0BFE));
}


INLINE void led__off(void) { 
    mcp251x__write(MCP251X_REGISTER_BFPCTRL, 0);
}


#endif