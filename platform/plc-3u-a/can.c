#include "device.h"
#include "platform/plc-3u-a/can.h"

#include "cpu/avr/drivers/mcp251x/bitdefs.h"
#include "cpu/avr/drivers/mcp251x/registers.h"
#include "cpu/avr/drivers/mcp251x/opmodes.h"
#include "cpu/avr/drivers/mcp251x/struct.h"


// RX Filters 0-2
extern mcp251x_message_id rxf0_2[3] = {
    RXF0, RXF1, RXF2
};

// RX Filters 3-5
extern mcp251x_message_id rxf3_5[3] = {
    RXF3, RXF4, RXF5
};

// RX Masks 0 and 1
extern mcp251x_message_id rxm0_1[2] = {
    RXM0, RXM1
};
