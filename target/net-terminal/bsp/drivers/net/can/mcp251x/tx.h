#ifndef __DRIVERS__NET__CAN__MCP251X__TX_H
#define __DRIVERS__NET__CAN__MCP251X__TX_H

#include <avr/pgmspace.h>

#include "cpu/avr/drivers/net/can/mcp251x/bitdefs.h"
#include "cpu/avr/drivers/net/can/mcp251x/registers.h"
#include "cpu/avr/drivers/net/can/mcp251x/opmodes.h"
#include "cpu/avr/drivers/net/can/mcp251x/struct.h"
#include "cpu/avr/drivers/net/can/mcp251x/instructions.h"
#include "cpu/avr/drivers/net/can/mcp251x/operations.h"

// TX Buffer 1 Header
extern mcp251x_frame_header can__txb1_h PROGMEM;

// TX Buffer 2 Header
extern mcp251x_frame_header can__txb2_h PROGMEM;


/**
 * Performs configuration of MCP251x message transmission module.
 * Uploads all the data that remains constant during the operation of the device
 * - TX Buffer 1 header
 * - TX Buffer 2 header
 */ 
INLINE void mcp251x__tx__init(void);

#endif

