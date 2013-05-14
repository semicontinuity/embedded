#ifndef __DRIVERS__NET__CAN__MCP251X__RX_H
#define __DRIVERS__NET__CAN__MCP251X__RX_H

#include <avr/pgmspace.h>

#include "cpu/avr/drivers/net/can/mcp251x/bitdefs.h"
#include "cpu/avr/drivers/net/can/mcp251x/registers.h"
#include "cpu/avr/drivers/net/can/mcp251x/opmodes.h"
#include "cpu/avr/drivers/net/can/mcp251x/struct.h"
#include "cpu/avr/drivers/net/can/mcp251x/instructions.h"


// RX Filters 0-2 (uploaded as one piece)
extern mcp251x_message_id can__rxf0_2[3] PROGMEM;

// RX Filters 3-5 (uploaded as one piece)
extern mcp251x_message_id can__rxf3_5[3] PROGMEM;

// RX Masks 0 and 1 (uploaded as one piece)
extern mcp251x_message_id can__rxm0_1[2] PROGMEM;


/**
 * Performs configuration of MCP251x message reception module.
 * Uploads all the data that remains constant during the operation of the device
 * - Masks
 * - Filters
 */ 
INLINE void mcp251x__rx__init(void);

#endif

