#include <avr/interrupt.h>
#include <stdint.h>

#include "packet.h"
#include "drivers/out/mcp251x_select.h"
#include "can_service.h"
#include "usart_tx_q.h"

#include "cpu/avr/asm.h"


uint8_t can_rx_buffer[PACKET_LENGTH] __attribute__ ((section (".noinit")));


static void can_service__handle_rx(void) {
    mcp251x_select__run(mcp251x__read_bytes(can_rx_buffer, MCP251X_REGISTER_RXB0SIDH, sizeof(can_rx_buffer)));

    volatile register uint8_t *packet	asm("r28");
    LOAD_ADDRESS(packet, can_rx_buffer);
    usart_tx_q__put_if_not_full(packet__copy());
}


// invoked on ANY change
CAN_CONTROLLER_INTERRUPT {
    if (bit_is_clear(PINC, 3)) {
        // interrupt flag for INT0 cleared automatically(?)
        // The only source of interrupt is from RX buffer 0
        can_service__handle_rx();

        // Clear all interrupts
        mcp251x_select__run(mcp251x__write(MCP251X_REGISTER_CANINTF, 0));
    }
    RETI();
}
