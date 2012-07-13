#ifndef __CONFIG__CAN_H
#define __CONFIG__CAN_H


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


#endif