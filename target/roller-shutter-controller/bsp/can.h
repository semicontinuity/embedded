// =============================================================================
// CAN Networking initialization.
//
// Performs MCP251x controller configuration.
// Uploads all the data that are set in the Configuration mode of MCP251X:
//
// - Configuration registers
// - Masks
// - Filters
//
// When the data are uploaded, the controller is switched into Normal Mode.
//
// The following constants must be defined:
//
// - CANP_DEVICE_NET	network id
// - CANP_DEVICE_ADDR	address in the network
//
// See conf.h for the description of constants
// that must be defined for the configuration registers.
// =============================================================================

#ifndef __CAN_H
#define __CAN_H

#include <util/delay.h>

#include "can_selector.h"

#include "cpu/avr/drivers/net/can/mcp251x/bitdefs.h"
#include "cpu/avr/drivers/net/can/mcp251x/conf.h"
#include "cpu/avr/drivers/net/can/mcp251x/registers.h"
#include "cpu/avr/drivers/net/can/mcp251x/opmodes.h"
#include "cpu/avr/drivers/net/can/mcp251x/struct.h"
#include "cpu/avr/drivers/net/can/mcp251x/operations.h"


// RX Filters 0-2
extern mcp251x_message_id rxf0_2[3] PROGMEM;

// RX Filters 3-5
extern mcp251x_message_id rxf3_5[3] PROGMEM;

// RX Masks 0 and 1
extern mcp251x_message_id rxm0_1[2] PROGMEM;


#ifdef MCP251X__CNF1
#  error "MCP251X__CNF1 is already defined"
#endif
#ifdef MCP251X__CNF2
#  error "MCP251X__CNF2 is already defined"
#endif
#ifdef MCP251X__CNF3
#  error "MCP251X__CNF3 is already defined"
#endif

#define MCP251X__CNF1 (\
  (MCP251X__CONF__SYNC_JUMP_WIDTH_BITS)     << MCP251X_SJW0   | \
  (MCP251X__CONF__BAUD_RATE_PRESCALER_BITS) << MCP251X_BRP0     \
)
#define MCP251X__CNF2 (\
  (MCP251X__CONF__BIT_TIME_LENGTH_MODE) << MCP251X_BLTMODE    | \
  (MCP251X__CONF__BUS_SAMPLING_MODE)    << MCP251X_SAM        | \
  (MCP251X__CONF__PROP_SEGMENT_1_BITS)  << MCP251X_PHSEG10    | \
  (MCP251X__CONF__PROP_SEGMENT_BITS)    << MCP251X_PRSEG0       \
)
#define MCP251X__CNF3 (\
  (MCP251X__CONF__CLKOUT_MODE)          << MCP251X_SOF        | \
  (MCP251X__CONF__WAKEUP_FILTER_MODE)   << MCP251X_WAKFIL     | \
  (MCP251X__CONF__PROP_SEGMENT_2_BITS)  << MCP251X_PHSEG20      \
)

inline static void can__init(void) {
    // Rely on HW reset 
    can_selector__run(mcp251x_reset());

    _delay_us(50); // >2

    can_selector__run(mcp251x_write_byte (MCP251X_REGISTER_CNF1, MCP251X__CNF1));
    can_selector__run(mcp251x_write_byte (MCP251X_REGISTER_CNF2, MCP251X__CNF2));
    can_selector__run(mcp251x_write_byte (MCP251X_REGISTER_CNF3, MCP251X__CNF3));

    can_selector__run(mcp251x_write_bytes_progmem ((uint8_t* PROGMEM)rxf0_2, MCP251X_REGISTER_RXF0SIDH, sizeof(rxf0_2)));
    can_selector__run(mcp251x_write_bytes_progmem ((uint8_t* PROGMEM)rxf3_5, MCP251X_REGISTER_RXF3SIDH, sizeof(rxf3_5)));
    can_selector__run(mcp251x_write_bytes_progmem ((uint8_t* PROGMEM)rxm0_1, MCP251X_REGISTER_RXM0SIDH, sizeof(rxm0_1)));
}


inline void can__start(void) {
    can_selector__run(mcp251x_write_byte (MCP251X_REGISTER_CANCTRL, MCP251X_OPMODE_NORMAL));
}

endif