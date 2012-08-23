// =============================================================================
// CAN Networking service.
//
//
// When the data are uploaded, the controller is switched into Normal Mode.
//
// The following constants must be defined:
//
// - CANP_DEVICE_NET	network id
// - CANP_DEVICE_ADDR	address in the network
// =============================================================================

#include "can.h"
#include <avr/pgmspace.h>

#include "cpu/avr/drivers/net/can/mcp251x/struct.h"
#include "cpu/avr/drivers/net/can/mcp251x/canp.h"


// Filters and mask for RX Buffer 0
#define RXM0	CANP_MASK	(                 CANP_RXM0_TAG, CANP_RXM0_CPTY_NET, CANP_RXM0_CPTY_ADDR, CANP_RXM0_HOST_NET, CANP_RXM0_HOST_ADDR, 0, 0, CANP_RXM0_REPORT)
#define RXF0	CANP_HEADER     (CANP_RXF0_EXIDE, CANP_RXF0_TAG, CANP_RXF0_CPTY_NET, CANP_RXF0_CPTY_ADDR, CANP_RXF0_HOST_NET, CANP_RXF0_HOST_ADDR, 0, 0, CANP_RXF0_REPORT)
#define RXF1	CANP_HEADER     (CANP_RXF1_EXIDE, CANP_RXF1_TAG, CANP_RXF1_CPTY_NET, CANP_RXF1_CPTY_ADDR, CANP_RXF1_HOST_NET, CANP_RXF1_HOST_ADDR, 0, 0, CANP_RXF1_REPORT)


// Filters and mask for RX Buffer 1
#define RXM1	CANP_MASK	(                 CANP_RXM0_TAG, CANP_RXM1_CPTY_NET, CANP_RXM1_CPTY_ADDR, CANP_RXM1_HOST_NET, CANP_RXM1_HOST_ADDR, 0, 0, CANP_RXM1_REPORT)
#define RXF2	CANP_HEADER     (CANP_RXF2_EXIDE, CANP_RXF2_TAG, CANP_RXF2_CPTY_NET, CANP_RXF2_CPTY_ADDR, CANP_RXF2_HOST_NET, CANP_RXF2_HOST_ADDR, 0, 0, CANP_RXF2_REPORT)
#define RXF3	CANP_HEADER     (CANP_RXF3_EXIDE, CANP_RXF3_TAG, CANP_RXF3_CPTY_NET, CANP_RXF3_CPTY_ADDR, CANP_RXF3_HOST_NET, CANP_RXF3_HOST_ADDR, 0, 0, CANP_RXF3_REPORT)
#define RXF4	CANP_HEADER     (CANP_RXF4_EXIDE, CANP_RXF4_TAG, CANP_RXF4_CPTY_NET, CANP_RXF4_CPTY_ADDR, CANP_RXF4_HOST_NET, CANP_RXF4_HOST_ADDR, 0, 0, CANP_RXF4_REPORT)
#define RXF5	CANP_HEADER     (CANP_RXF5_EXIDE, CANP_RXF5_TAG, CANP_RXF5_CPTY_NET, CANP_RXF5_CPTY_ADDR, CANP_RXF5_HOST_NET, CANP_RXF5_HOST_ADDR, 0, 0, CANP_RXF5_REPORT)


// RX Filters 0-2
mcp251x_message_id can__rxf0_2[3] PROGMEM = {RXF0, RXF1, RXF2};

// RX Filters 3-5
mcp251x_message_id can__rxf3_5[3] PROGMEM = {RXF3, RXF4, RXF5};

// RX Masks 0 and 1
mcp251x_message_id can__rxm0_1[2] PROGMEM = {RXM0, RXM1};


// TX Buffer 1 Header
mcp251x_frame_header can__txb1_h PROGMEM = {
    CANP_HEADER(
        CANP_EXT_ID, CANP_DEVICE_TAG,
        CANP_MANAGER_NET, CANP_MANAGER_ADDR,
        CANP_DEVICE_NET, CANP_DEVICE_ADDR,
        CANP_OUT, CANP_RAM, CANP_TXB1_REPORT_ID
    ),
    CANP_TXB1_REPORT_SIZE
};

// TX Buffer 2 Header
mcp251x_frame_header can__txb2_h PROGMEM = {
    CANP_HEADER(
        CANP_EXT_ID, CANP_DEVICE_TAG,
        CANP_MANAGER_NET, CANP_MANAGER_ADDR,
        CANP_DEVICE_NET, CANP_DEVICE_ADDR,
        CANP_OUT, CANP_RAM, CANP_TXB2_REPORT_ID
    ),
    CANP_TXB2_REPORT_SIZE
};
