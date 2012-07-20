#include "device.h"
#include <avr/io.h>

#include "device.h"

#include "can_tx_q.h"
#include "can_tx.h"
#include "packet.h"

#include "cpu/avr/asm.h"
#include "util/bitops.h"

#include "cpu/avr/drivers/net/can/mcp251x/registers.h"
#include "cpu/avr/drivers/net/can/mcp251x/instructions.h"
#include "cpu/avr/drivers/net/can/mcp251x/operations.h"



CAN_TX_Q_THREAD_INTERRUPT {

    if (!can_tx_q__empty()) {
        can_tx_q__tail__to_z();
        can_tx_q__tail__move();

        volatile register uint8_t *packet asm("r30");
        MCP251X_SPI_COMM (mcp2515_load_tx_buffer (packet, MCP251X_INSTRUCTION_LOAD_BUFFER_0_SIDH, PACKET_LENGTH));
        MCP251X_SPI_COMM (mcp2515_request_to_send (MCP251X_INSTRUCTION_REQUEST_TO_SEND | MCP251X_INSTRUCTION_REQUEST_TO_SEND_B0));
    }
    else {
        can_tx_q_thread__enabled__set(0);
    }
    RETI();
}


INLINE void can_tx_q__on_not_empty(void) {
    // Wake up the can_tx_q_thread, if it sleeps
    can_tx_q_thread__enabled__set(1);
}
