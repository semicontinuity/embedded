#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "pwm.h"

#include "cpu/avr/gpio.h"
#include "cpu/avr/util/debug.h"
#include "cpu/avr/drivers/net/can/mcp251x/bitdefs.h"
#include "cpu/avr/drivers/net/can/mcp251x/instructions.h"
#include "cpu/avr/drivers/net/can/mcp251x/registers.h"
#include "cpu/avr/drivers/net/can/mcp251x/operations.h"
#include "cpu/avr/drivers/net/can/mcp251x/struct.h"
#include "cpu/avr/drivers/net/can/mcp251x/interrupt-codes.h"

#include "cpu/avr/drivers/net/can/mcp251x/canp.h"


#define COPY_8_BYTES(dst_start, src_start)	do {	\
    uint8_t* dst = (uint8_t*)dst_start; \
    uint8_t* src = (uint8_t*)src_start;	\
    *dst++ = *src++;	\
    *dst++ = *src++;	\
    *dst++ = *src++;	\
    *dst++ = *src++;	\
    *dst++ = *src++;	\
    *dst++ = *src++;	\
    *dst++ = *src++;	\
    *dst++ = *src++;	\
} while(0)


static volatile mcp251x_message_buffer buffer;


static void can_service__handle_rx(void) {
    mcp251x__read_bytes((uint8_t*)&buffer.header, MCP251X_REGISTER_RXB0SIDH, sizeof(mcp251x_frame_header));
    uint8_t slot = CANP_SLOT_BITS(buffer.header.id);

    // Assume that extended frame was received.
    // Check if it was an Remote Transmission Request: use RTR bit in DLC (extended frames only)
    if (buffer.header.dlc & _BV(MCP251X_RTR)) {
        // Received GET request
        // Leave only data length in dlc field, because the same buffer will be used for sending response without RTR set.
        // The message ID of the response is the same as for request, so it can be reused.
        buffer.header.dlc &= 0x0F;
        
        if (CANP_AUX_BITS(buffer.header.id)) {
            // Read ROM
            memcpy_P((void*)buffer.data, (PGM_VOID_P)(slot * 8), buffer.header.dlc);
            mcp2515__load_tx_buffer ((uint8_t*)&buffer, MCP251X_INSTRUCTION_LOAD_BUFFER_0_SIDH, sizeof(buffer));
            mcp2515__request_to_send (MCP251X_INSTRUCTION_REQUEST_TO_SEND | MCP251X_INSTRUCTION_REQUEST_TO_SEND_B0);
            // TODO: check TXREQ
        }
        else {
            // Read RAM request
            if (slot == 0) {
                COPY_8_BYTES(buffer.data, colors);
                mcp2515__load_tx_buffer ((uint8_t*)&buffer, MCP251X_INSTRUCTION_LOAD_BUFFER_0_SIDH, sizeof(buffer));
                mcp2515__request_to_send (MCP251X_INSTRUCTION_REQUEST_TO_SEND | MCP251X_INSTRUCTION_REQUEST_TO_SEND_B0);
                // TODO: check TXREQ
            }
        }
    }
    else {
        // Received PUT request
        if (!CANP_AUX_BITS(buffer.header.id) && slot == 0) {
            mcp251x__read_bytes((uint8_t*)buffer.data, MCP251X_REGISTER_RXB0D0, sizeof(buffer.data));
            COPY_8_BYTES(colors, buffer.data);
        }        
    }
}


/**
 *  Handler for the interrupt from MCP2515 CAN controller (falling edge).
 */
ISR(INT1_vect) {
    // interrupt flag for INT1 cleared automatically
    // The only source of interrupt is from RX buffer 0
    can_service__handle_rx();

    // Clear all interrupts
    mcp251x__write(MCP251X_REGISTER_CANINTF, 0);
}


/*
static void handle_error(void) {
    uint8_t eflg;
    eflg = mcp251x__read(MCP251X_REGISTER_EFLG);
}
*/

/*
ISR(INT1_vect) {
    // interrupt flag for INT1 cleared automatically
    uint8_t icod_bits;
    icod_bits = mcp251x__read(MCP251X_REGISTER_CANSTAT) & ICOD_BITS_MASK;
    
    switch(icod_bits) {
//    case ICOD_BITS_MASKED(MCP251X_ICOD_ERROR):
//        break;
//    case ICOD_BITS_MASKED(MCP251X_ICOD_WAK):
//        break;
//    case ICOD_BITS_MASKED(MCP251X_ICOD_TX0):
//        break;
    case ICOD_BITS_MASKED(MCP251X_ICOD_RX0):
        handle_rx();
        break;
    }
}
*/