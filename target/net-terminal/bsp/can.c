// =============================================================================
// CAN Controller driver.
//
// The following symbols must be defined in can__conf.h:
//
// RXF0, RXF1, RXF2, RXF3, RXF4, RXF5
// RXM0, RXM1
// TXB1H, TXB2H
// =============================================================================

#include "can.h"
#include <avr/pgmspace.h>

#include "cpu/avr/drivers/net/can/mcp251x/struct.h"

