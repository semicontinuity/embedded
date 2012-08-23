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
#define RXM0	CANP_MASK	(CANP_RXM0_TAG, 0, 0, CANP_COMPARE_HOST_NET,	CANP_COMPARE_HOST_ADDR,	0, 0, 0)
#define RXF0	CANP_FILT_EXT	(CANP_RXF0_TAG, 0, 0, CANP_DEVICE_NET,		CANP_DEVICE_ADDR,	0, 0, 0) /* All EXT frames addressed to device */
#define RXF1	CANP_FILT_STD	(CANP_RXF1_TAG, 0, 0, 0, 0, 0, 0, 0) /* All STD frames => will never be triggered */


// Filters and mask for RX Buffer 1
#define RXM1	CANP_MASK	(CANP_RXM0_TAG, 0, 0, 0, 0, 0, 0, 0) /* Don't compare */
#define RXF2	CANP_FILT_STD	(CANP_RXF2_TAG, 0, 0, 0, 0, 0, 0, 0) /* All STD frames => will never be triggered */
#define RXF3	CANP_FILT_STD	(CANP_RXF3_TAG, 0, 0, 0, 0, 0, 0, 0) /* All STD frames => will never be triggered */
#define RXF4	CANP_FILT_STD	(CANP_RXF4_TAG, 0, 0, 0, 0, 0, 0, 0) /* All STD frames => will never be triggered */
#define RXF5	CANP_FILT_STD	(CANP_RXF5_TAG, 0, 0, 0, 0, 0, 0, 0) /* All STD frames => will never be triggered */


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
