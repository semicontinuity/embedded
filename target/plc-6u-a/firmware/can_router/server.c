#include "device.h"
#include <avr/io.h>

#include "server.h"
#include "debug.h"

#include "usart_tx_q.h"

#include "cpu/avr/asm.h"

#include "cpu/avr/drivers/net/can/mcp251x/registers.h"
#include "cpu/avr/drivers/net/can/mcp251x/instructions.h"
#include "cpu/avr/drivers/net/can/mcp251x/operations.h"

// Host to CAN router protocol:
#define PROTOCOL_CMD_READ_MEM   (0)
#define PROTOCOL_CMD_WRITE_MEM  (1)
#define PROTOCOL_CMD_READ_CAN   (2)
#define PROTOCOL_CMD_WRITE_CAN  (3)



inline void server__process_packet__read_mem(void) {
    // The only supported query is "memory dump":
    // Return 8 bytes of memory, starting at location (endpoint)*8.
    // The response to the host query is sent to USART (via usart_tx_queue)

    if (usart_tx_q__not_empty()) {
        usart_tx_q__write__begin();

        // Create response in usart_tx_q: (header = copy of request header) + (data = memory contents)

        // Copy header (5 bytes)
        // -------------------------------------------------------------------------------------------

        YPLUS_TO_ZPLUS();
        YPLUS_TO_ZPLUS();
        YPLUS_TO_ZPLUS();
        YPLUS_TO_ZPLUS();
        YPLUS_TO_ZPLUS();

        // Copy the specified memory contents (8 bytes).
        // -------------------------------------------------------------------------------------------

        // Prepare to copy: set up Y to point to the memory address requested
        // (first two bytes of payload)
        __asm__ __volatile__ (
            "ldd r28, Y+0\n\t"
            "ldd r29, Y+1\n\t"
        );

        // Copy data (8 bytes)
        YPLUS_TO_ZPLUS();
        YPLUS_TO_ZPLUS();
        YPLUS_TO_ZPLUS();
        YPLUS_TO_ZPLUS();
        YPLUS_TO_ZPLUS();
        YPLUS_TO_ZPLUS();
        YPLUS_TO_ZPLUS();
        YPLUS_TO_ZPLUS();

        usart_tx_q__write__end();
    }
}


/**
 * Processed the packet addressed to the server.
 * @param Y register - the pointer to the packet
 */
inline void server__process_packet__read_can(void) {
    volatile register uint8_t *packet	asm("r28");
/*
    if (usart_tx_q__remaining > 0) {
        usart_tx_q__remaining--;

        // Prepare to copy: set up Z to point to the head of the usart_tx_q.
        __asm__ __volatile__ (
            "mov	r30, %0			\n\t"
            "ldi	r31, hi8(usart_tx_q)	\n\t"
             :: "r"(usart_tx_q__w_ptr__lo8)
        );

        // Copy header (5 bytes)
        YPLUS_TO_ZPLUS();
        YPLUS_TO_ZPLUS();
        YPLUS_TO_ZPLUS();
        YPLUS_TO_ZPLUS();
        YPLUS_TO_ZPLUS();

*/

//        WITH_CS (mcp251x_read_bytes(usart_tx_q__w_ptr + 5, packet[PACKET__OFFSETOF_A_LO], 8));
//        WITH_CS (mcp251x_read_bytes(usart_rx_buffer, 0x28, 8));
    uint8_t d;
    MCP251X_SPI_COMM (d = mcp251x_read_byte(*packet));
    debug__write(d);

/*
        MOVW(packet, usart_rx_buffer);
        // Copy data (8 bytes)
        YPLUS_TO_ZPLUS();
        YPLUS_TO_ZPLUS();
        YPLUS_TO_ZPLUS();
        YPLUS_TO_ZPLUS();
        YPLUS_TO_ZPLUS();
        YPLUS_TO_ZPLUS();
        YPLUS_TO_ZPLUS();
        YPLUS_TO_ZPLUS();


        // Move head pointer
        // Higher 8 bits are not touched, thus the pointer automatically wraps to the start of the queue.
        usart_tx_q__w_ptr__lo8 += PACKET_Q_STRIDE;

        // Wake up usart_tx_q_thread, if it sleeps
        usart_tx_q_thread__enabled__set();
    }
*/
}


/**
 * Processed the packet addressed to the server.
 * @param Y register - the pointer to the packet
 */
INLINE void server__process_packet(void) {
    register uint8_t *packet	asm("r28");

    switch (packet[0]) { // TODO
    case PROTOCOL_CMD_READ_MEM:
/*
    loop_until_bit_is_set(UCSRA, UDRE);
    __asm__ __volatile__("sts 0x00C6, r31");

    loop_until_bit_is_set(UCSRA, UDRE);
    __asm__ __volatile__("sts 0x00C6, r30");

    loop_until_bit_is_set(UCSRA, UDRE);
    __asm__ __volatile__("sts 0x00C6, r29");

    loop_until_bit_is_set(UCSRA, UDRE);
    __asm__ __volatile__("sts 0x00C6, r28");
*/
        server__process_packet__read_mem();
        break;
    case PROTOCOL_CMD_READ_CAN:
        server__process_packet__read_can();
        break;
    }
}