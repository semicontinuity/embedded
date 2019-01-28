#include <avr/io.h>

#include "drivers/out/mcp251x_select.h"

#include "can_tx_q.h"
#include "can_tx.h"
#include "packet.h"

#include "cpu/avr/asm.h"
#include "util/bitops.h"

#include "cpu/avr/drivers/net/can/mcp251x/registers.h"
#include "cpu/avr/drivers/net/can/mcp251x/instructions.h"
#include "cpu/avr/drivers/net/can/mcp251x/operations.h"

/**
 * Transmit the CAN packet
 * @param register Z - packet pointer
 */
inline void can_tx__transmit_packet(void) {
    register const uint8_t *packet asm("r30");
    mcp251x_select__run(mcp2515__load_tx_buffer (packet, MCP251X_INSTRUCTION_LOAD_BUFFER_0_SIDH, PACKET_LENGTH));
    mcp251x_select__run(mcp2515__request_to_send (MCP251X_INSTRUCTION_REQUEST_TO_SEND | MCP251X_INSTRUCTION_REQUEST_TO_SEND_B0));
}


CAN_TX_Q_THREAD_INTERRUPT {
    // The queue can_tx_q is not empty.
    // If it becomes empty after processing of the packet, suspend can_tx_q_thread.
    can_tx_q__get(can_tx__transmit_packet(), can_tx_q_thread__enabled__set(0));
    RETI();
}


/**
 * Invoked when the packet has been added to the can_tx queue.
 */
INLINE void can_tx_q__on_not_empty(void) {
    // Wake up the can_tx_q_thread, if it sleeps
    can_tx_q_thread__enabled__set(1);
}
