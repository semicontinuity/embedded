// =============================================================================
// MCP251X CAN Controller driver - interrupt handler.
// =============================================================================

#include "kernel__rx__handler.h"
#include "kernel__tx__handler.h"

#include "drivers/net/can/mcp251x/int_handler.h"
#include "cpu/avr/drivers/net/can/mcp251x/bitdefs.h"
#include "cpu/avr/drivers/net/can/mcp251x/registers.h"
#include "cpu/avr/drivers/net/can/mcp251x/opmodes.h"
#include "cpu/avr/drivers/net/can/mcp251x/struct.h"
#include "cpu/avr/drivers/net/can/mcp251x/instructions.h"
#include "cpu/avr/drivers/net/can/mcp251x/operations.h"


INLINE void mcp251x__int_handler__start(void) {
    mcp251x__write(MCP251X_REGISTER_CANINTE, _BV(MCP251X_RX0IE)|_BV(MCP251X_RX1IE)|_BV(MCP251X_TX1IE)|_BV(MCP251X_TX2IE));
    mcp251x__write(MCP251X_REGISTER_CANCTRL, MCP251X_OPMODE_NORMAL);
}


/**
 *  Handler for the interrupt from MCP2515 CAN controller.
 */
INLINE void mcp2515__int_handler__run(void) {
    uint8_t status = mcp2515__read_status();

    if (status & (MCP251X__STATUS__RX0IF | MCP251X__STATUS__RX1IF)) {
        // Interrupt flag cleared automatically when proper RX buffer is read.
        kernel__rx__handle(mcp2515__rx__read_frame((uint8_t*)&kernel__frame));
    }
    else {
        uint8_t mask;
        if (status & (MCP251X__STATUS__TX1IF)) {
            mask = 1 << MCP251X_TX1IF;
        }
        else {
            // MCP251X__STATUS__TX2IF
            mask = 1 << MCP251X_TX2IF;
        }
        // clear corresponding interrupt
        mcp251x__bit_modify(MCP251X_REGISTER_CANINTF, mask, 0);
        kernel__tx__handle(mask);
    }
}
