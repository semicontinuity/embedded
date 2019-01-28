#ifndef __MCP251X__RX__CONF_H
#define __MCP251X__RX__CONF_H


#include "cpu/avr/drivers/net/can/mcp251x/ucan.h"


// Filters and mask for RX Buffer 0
#define RXM0    UCAN_MASK       (                 UCAN_RXM0_DST, UCAN_RXM0_OBJID, UCAN_RXM0_SRC, UCAN_RXM0_PORT, UCAN_RXM0_PARAM, UCAN_RXM0_MCAST)
#define RXF0	UCAN_HEADER     (UCAN_RXF0_EXIDE, UCAN_RXF0_DST, UCAN_RXF0_OBJID, UCAN_RXF0_SRC, UCAN_RXF0_PORT, UCAN_RXF0_PARAM, UCAN_RXF0_MCAST)
#define RXF1	UCAN_HEADER     (UCAN_RXF1_EXIDE, UCAN_RXF1_DST, UCAN_RXF1_OBJID, UCAN_RXF1_SRC, UCAN_RXF1_PORT, UCAN_RXF1_PARAM, UCAN_RXF1_MCAST)

// Filters and mask for RX Buffer 1
#define RXM1    UCAN_MASK       (                 UCAN_RXM1_DST, UCAN_RXM1_OBJID, UCAN_RXM1_SRC, UCAN_RXM1_PORT, UCAN_RXM1_PARAM, UCAN_RXM1_MCAST)
#define RXF2	UCAN_HEADER     (UCAN_RXF2_EXIDE, UCAN_RXF2_DST, UCAN_RXF2_OBJID, UCAN_RXF2_SRC, UCAN_RXF2_PORT, UCAN_RXF2_PARAM, UCAN_RXF2_MCAST)
#define RXF3	UCAN_HEADER     (UCAN_RXF3_EXIDE, UCAN_RXF3_DST, UCAN_RXF3_OBJID, UCAN_RXF3_SRC, UCAN_RXF3_PORT, UCAN_RXF3_PARAM, UCAN_RXF3_MCAST)
#define RXF4	UCAN_HEADER     (UCAN_RXF4_EXIDE, UCAN_RXF4_DST, UCAN_RXF4_OBJID, UCAN_RXF4_SRC, UCAN_RXF4_PORT, UCAN_RXF4_PARAM, UCAN_RXF4_MCAST)
#define RXF5	UCAN_HEADER     (UCAN_RXF5_EXIDE, UCAN_RXF5_DST, UCAN_RXF5_OBJID, UCAN_RXF5_SRC, UCAN_RXF5_PORT, UCAN_RXF5_PARAM, UCAN_RXF5_MCAST)


#endif
