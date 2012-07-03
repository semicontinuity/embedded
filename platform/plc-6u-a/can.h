#ifndef __CAN_H
#define __CAN_H

#include "device.h"
#include <util/delay.h>
#include "cpu/avr/drivers/mcp251x/bitdefs.h"
#include "cpu/avr/drivers/mcp251x/registers.h"
#include "cpu/avr/drivers/mcp251x/opmodes.h"
#include "cpu/avr/drivers/mcp251x/struct.h"
#include "cpu/avr/drivers/mcp251x/operations.h"
#include <avr/pgmspace.h>


// RX Filters 0-2
extern mcp251x_message_id rxf0_2[3] PROGMEM;

// RX Filters 3-5
extern mcp251x_message_id rxf3_5[3] PROGMEM;

// RX Masks 0 and 1
extern mcp251x_message_id rxm0_1[2] PROGMEM;


static inline void can__init(void) {
    // Rely on HW reset 
    MCP251X_SPI_COMM (mcp251x_reset());
    _delay_us(50); // >2
    MCP251X_SPI_COMM (mcp251x_write_byte (MCP251X_REGISTER_CNF1, 0x07));
    MCP251X_SPI_COMM (mcp251x_write_byte (MCP251X_REGISTER_CNF2, 0x90));
    MCP251X_SPI_COMM (mcp251x_write_byte (MCP251X_REGISTER_CNF3, 0x02));

    MCP251X_SPI_COMM (mcp251x_write_bytes_progmem ((uint8_t* PROGMEM)rxf0_2, MCP251X_REGISTER_RXF0SIDH, sizeof(rxf0_2)));
    MCP251X_SPI_COMM (mcp251x_write_bytes_progmem ((uint8_t* PROGMEM)rxf3_5, MCP251X_REGISTER_RXF3SIDH, sizeof(rxf3_5)));
    MCP251X_SPI_COMM (mcp251x_write_bytes_progmem ((uint8_t* PROGMEM)rxm0_1, MCP251X_REGISTER_RXM0SIDH, sizeof(rxm0_1)));
}


inline void can__start(void) {
    MCP251X_SPI_COMM (mcp251x_write_byte (MCP251X_REGISTER_CANCTRL, MCP251X_OPMODE_NORMAL));
}

#endif