#include <avr/interrupt.h>
#include <stdint.h>

#include "packet.h"
#include "can_selector.h"
#include "can_service.h"
#include "usart_tx_q.h"

#include "cpu/avr/asm.h"


uint8_t can_rx_buffer[PACKET_LENGTH] __attribute__ ((section (".noinit")));


static void can_service__handle_rx(void) {
    can_selector__run(mcp251x_read_bytes(can_rx_buffer, MCP251X_REGISTER_RXB0SIDH, sizeof(can_rx_buffer)));

    volatile register uint8_t *packet	asm("r28");
    LOAD_ADDRESS(packet, can_rx_buffer);
    usart_tx_q__put_if_not_full(packet__copy());
}


CAN_CONTROLLER_INTERRUPT {
    // interrupt flag for INT0 cleared automatically
    // The only source of interrupt is from RX buffer 0
    can_service__handle_rx();

    // Clear all interrupts
    can_selector__run(mcp251x_write_one_byte(MCP251X_REGISTER_CANINTF, 0));

    RETI();
}
