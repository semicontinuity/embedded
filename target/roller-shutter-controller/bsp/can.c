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

#include "can.h"

#include "cpu/avr/drivers/net/can/mcp251x/bitdefs.h"
#include "cpu/avr/drivers/net/can/mcp251x/registers.h"
#include "cpu/avr/drivers/net/can/mcp251x/opmodes.h"
#include "cpu/avr/drivers/net/can/mcp251x/struct.h"
#include <avr/pgmspace.h>


#include "cpu/avr/drivers/net/can/mcp251x/canp.h"

// Filters and mask for RX Buffer 0
#define RXM0	CANP_MASK	(0, 0, 0, CANP_COMPARE_HOST_NET,	CANP_COMPARE_HOST_ADDR,	0, 0, 0)
#define RXF0	CANP_FILT_EXT	(0, 0, 0, CANP_DEVICE_NET,		CANP_DEVICE_ADDR,	0, 0, 0) /* All EXT frames addressed to device */
#define RXF1	CANP_FILT_STD	(0, 0, 0, 0, 0, 0, 0, 0) /* All STD frames => will never be triggered */


// Filters and mask for RX Buffer 1
#define RXM1	CANP_MASK	(0, 0, 0, 0, 0, 0, 0, 0) /* Don't compare */
#define RXF2	CANP_FILT_STD	(0, 0, 0, 0, 0, 0, 0, 0) /* All STD frames => will never be triggered */
#define RXF3	CANP_FILT_STD	(0, 0, 0, 0, 0, 0, 0, 0) /* All STD frames => will never be triggered */
#define RXF4	CANP_FILT_STD	(0, 0, 0, 0, 0, 0, 0, 0) /* All STD frames => will never be triggered */
#define RXF5	CANP_FILT_STD	(0, 0, 0, 0, 0, 0, 0, 0) /* All STD frames => will never be triggered */


// RX Filters 0-2
mcp251x_message_id rxf0_2[3] PROGMEM = {
    RXF0, RXF1, RXF2
};

// RX Filters 3-5
mcp251x_message_id rxf3_5[3] PROGMEM = {
    RXF3, RXF4, RXF5
};

// RX Masks 0 and 1
mcp251x_message_id rxm0_1[2] PROGMEM = {
    RXM0, RXM1
};
