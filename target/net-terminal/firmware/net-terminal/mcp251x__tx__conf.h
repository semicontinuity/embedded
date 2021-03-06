#ifndef __MCP251X__TX__CONF_H
#define __MCP251X__TX__CONF_H


#include "cpu/avr/drivers/net/can/mcp251x/canp.h"


// TXB1 and TXB2 headers
#define TXB1H   {CANP_HEADER    (CANP_TXB1_EXIDE, CANP_TXB1_TAG, CANP_TXB1_CPTY_NET, CANP_TXB1_CPTY_ADDR, CANP_TXB1_HOST_NET, CANP_TXB1_HOST_ADDR, CANP_TXB1_OWNER, CANP_TXB1_AUX, CANP_TXB1_REPORT_ID), CANP_TXB1_REPORT_SIZE}
#define TXB2H   {CANP_HEADER    (CANP_TXB2_EXIDE, CANP_TXB2_TAG, CANP_TXB2_CPTY_NET, CANP_TXB2_CPTY_ADDR, CANP_TXB2_HOST_NET, CANP_TXB2_HOST_ADDR, CANP_TXB2_OWNER, CANP_TXB2_AUX, CANP_TXB2_REPORT_ID), CANP_TXB2_REPORT_SIZE}


#endif