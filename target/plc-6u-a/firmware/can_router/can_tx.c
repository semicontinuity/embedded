#include "device.h"
#include <avr/io.h>

#include "device.h"

#include "can_tx_q.h"
#include "can_tx.h"
#include "packet.h"

#include "cpu/avr/asm.h"
#include "cpu/avr/bitops.h"

#include "cpu/avr/drivers/net/can/mcp251x/registers.h"
#include "cpu/avr/drivers/net/can/mcp251x/instructions.h"
#include "cpu/avr/drivers/net/can/mcp251x/operations.h"



CAN_TX_Q_THREAD_INTERRUPT {

    // TODO: optimize
    // if queue is not empty, remove packet from tail and ask 'usart_tx_thread' to transmit it to UART
    if (can_tx_q__remaining != CAN_TX_Q_LENGTH) {
        can_tx_q__remaining++;

        uint8_t *packet;
        __asm__ __volatile__ (				
          "mov %A0, %1\n\t"			
          "ldi %B0, hi8(can_tx_q)\n\t"			
          : "=z"(packet) : "r"(can_tx_q__r_ptr__lo8)	
        );						
         
//        LOAD_ADDRESS_HI8(packet, can_tx_q);
//        SET_LO8_OF	(packet, can_tx_q__r_ptr__lo8);

        // Remove the packet at the tail tail by moving the tail pointer
        // Higher 8 bits are not touched, thus the pointer automatically wraps to the start of the queue.
        can_tx_q__r_ptr__lo8 += PACKET_Q_STRIDE;

        MCP251X_SPI_COMM (mcp2515_load_tx_buffer (packet, MCP251X_INSTRUCTION_LOAD_BUFFER_0_SIDH, PACKET_LENGTH));
//        MCP251X_SPI_COMM (mcp251x_write_bytes (packet, MCP251X_REGISTER_TXB0SIDH, PACKET_LENGTH));
//        MCP251X_SPI_COMM (mcp251x_write_byte (MCP251X_REGISTER_TXB0SIDH, packet[0]));
        MCP251X_SPI_COMM (mcp2515_request_to_send (MCP251X_INSTRUCTION_REQUEST_TO_SEND | MCP251X_INSTRUCTION_REQUEST_TO_SEND_B0));
    }
    else {
        // TODO optimize to sleep right after can_tx_q__r_ptr__lo8 += PACKET_Q_STRIDE: check if it has reached w_ptr.
        can_tx_q_thread__enabled__clear();
    }

    __asm__ (
        "reti		\n\t"
    );
}
