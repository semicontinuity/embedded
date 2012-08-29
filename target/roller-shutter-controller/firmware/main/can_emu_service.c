// =============================================================================
// CAN service emulator.
// Handles CAN communications (services incoming requests).
// Extends comm_service.
// =============================================================================

#include <avr/io.h>
#include <stdint.h>

#include "can_emu_service.h"
#include "comm_service.h"
#include "comm_service__rx.h"
#include "cpu/avr/asm.h"



/**
 * Emulate MCP2515 masks and filters.
 */
inline static void can_service__on_packet_transferred(void) {
    const uint8_t slot = CANP_SLOT_BITS(comm_service__buffer.header.id);
    if (comm_service__buffer.header.id.eid8 == ((CANP_DEVICE_NET<<5) | CANP_DEVICE_ADDR)) {
        if (CANP_AUX_BITS(comm_service__buffer.header.id)) {
            // SYSTEM
            comm_service__handle_rx((slot & 0x80) ? CANP_FILTER__ADMIN : CANP_FILTER__DESCRIPTOR_MEMORY);
        }
        else {
            // USER
            comm_service__handle_rx(CANP_FILTER__USER);
        }        
    }
    else if (comm_service__buffer.header.id.eid8 == ((CANP_MCAST_NET<<5) | CANP_MCAST_ADDR)) {
        if (!CANP_AUX_BITS(comm_service__buffer.header.id)) {
            comm_service__handle_rx(CANP_FILTER__USER_MCAST);
        }
    }
}


inline static void usart_rx_thread__on_packet_transferred(void) {
    // handle
    can_service__on_packet_transferred();

    // prepare to receive the next packet
    usart_rx_thread__init();
}


USART_RX_THREAD_INTERRUPT {
    STORE_TO_XPLUS(usart__in__peek());

    DEC(usart_rx_thread__size);
    IF_ZERO(usart_rx_thread__on_packet_transferred());
    RETI();    
}
