#include <avr/io.h>

#include "packet.h"
#include "can_selector.h"

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

/**
 * Create the response packet for the Memory Request packet
 * @param register Y - request packet pointer
 * @param register Z - response packet pointer
 */
inline static void server__handle_packet__read_mem(void) {
    // Create response: (header = copy of request header) + (data = memory contents)
    packet__copy_header();

    // Copy the specified memory contents (8 bytes).
    // -------------------------------------------------------------------------------------------
    // Set up Y to point to the memory address requested
    // (first two bytes of payload)
    volatile register uint8_t *address;
    volatile register uint8_t *packet	asm("r28");
    LDD_Y_U16(address, 0);
    MOVW(packet, address);
    packet__copy_payload();
}


/**
 * Read memory query.
 * The first 2 bytes of request packet payload contain the memory address to be read.
 * The 8 bytes of memory from the specified address are placed into the response packet payload,
 * and the response is placed into USART TX queue.
 */
inline static void server__process_packet__read_mem(void) {
    usart_tx_q__put_if_not_full(server__handle_packet__read_mem());
}


/**
 * Processed the packet addressed to the server.
 * @param Y register - the pointer to the packet
 */
inline static void server__process_packet__read_can(void) {
    volatile register uint8_t *packet	asm("r28");
    uint8_t d;
    can_selector__run(d = mcp251x_read_byte(*packet));
    debug__write(d);
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