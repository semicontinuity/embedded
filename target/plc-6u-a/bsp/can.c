#include "device.h"
#include "can.h"
#include "cpu/avr/drivers/net/can/mcp251x/struct.h"
#include <avr/pgmspace.h>


// RX Filters 0-2
const mcp251x_message_id rxf0_2[3] PROGMEM = {
    RXF0, RXF1, RXF2
};

// RX Filters 3-5
const mcp251x_message_id rxf3_5[3] PROGMEM = {
    RXF3, RXF4, RXF5
};

// RX Masks 0 and 1
const mcp251x_message_id rxm0_1[2] PROGMEM = {
    RXM0, RXM1
};
