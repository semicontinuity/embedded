#include "device.h"
#include <avr/io.h>

#include "server.h"
#include "debug.h"

#include "usart_tx.h"
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



inline void handle_read_mem(void) {
    register uint8_t *packet	asm("r28");
    register uint8_t *packet_start = packet;

    // The only supported query is "memory dump":
    // Return 8 bytes of memory, starting at location (endpoint)*8.
    // The response to the host query is sent to USART (via usart_tx_queue)

    // TODO: Optimize with dec, inc, e.g. make macro "TRY_DEC"
    if (usart_tx_q__remaining > 0) {
        usart_tx_q__remaining--;

        // Create response in usart_tx_q: (header = copy of request header) + (data = memory contents)

        // Prepare to copy: set up r25:r24 to point to the memory address requested (no multiplication):
        // Format of 0th byte is: 7 -> [PRIO:1, ENDPOINT:7] <- 0. Discard PRIO when shifting.
/*
        __asm__ __volatile__ (
            "clr    r25			\n\t"
            "ld	r24, Y			\n\t"
            "lsl 	r24			\n\t"

            "lsl 	r24			\n\t"
            "rol 	r25			\n\t"

            "lsl 	r24			\n\t"
            "rol 	r25			\n\t"
        );
*/          


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

        // Copy 8 bytes from memory.

        // Prepare to copy: set up Y to point to the memory address requested (address computed above and saved to r25:r24)
        MOVW(packet, ((*packet_start + 0) & 0x7F) << 3);

/*            __asm__ __volatile__(
            "movw	r28, r24		\n\t"
        );
*/

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
        usart_tx_q_thread__enabled__set(1);
    }
}


inline void handle_read_can(void) {
    register uint8_t *packet	asm("r28");
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
        handle_read_mem();
        break;
    case PROTOCOL_CMD_READ_CAN:
        handle_read_can();
        break;
    }
}