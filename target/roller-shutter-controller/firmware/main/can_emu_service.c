// =============================================================================
// CAN service emulator.
// CAN communications are emulated with USART (13-byte packets).
// Handles CAN communications (services incoming requests).
// Extends kernel.
// =============================================================================

#include <avr/io.h>
#include <stdint.h>

#include "can_emu_service.h"
#include "kernel.h"
#include "kernel__rx__handler.h"
#include "cpu/avr/asm.h"


/**
 * Emulate MCP2515 masks and filters.
 */
inline static void can_emu_service__on_packet_transferred(void) {
    const uint8_t slot = CANP_SLOT_BITS(kernel__frame.header.id);
    if (kernel__frame.header.id.eid8 == ((CANP_DEVICE_NET<<5) | CANP_DEVICE_ADDR)) {
        if (CANP_AUX_BITS(kernel__frame.header.id)) {
            // SYSTEM
            kernel__rx__handle((slot & 0x80) ? CANP_FILTER__ADMIN : CANP_FILTER__DESCRIPTOR_MEMORY);
        }
        else {
            // USER
            kernel__rx__handle(CANP_FILTER__USER);
        }        
    }
    else {
        if (kernel__frame.header.id.eid8 == ((CANP_MCAST_NET<<5) | CANP_MCAST_ADDR)) {
            if (!CANP_AUX_BITS(kernel__frame.header.id)) {
                kernel__rx__handle(CANP_FILTER__USER_MCAST);
            }
        }
    }
}


inline static void usart_rx_thread__on_packet_transferred(void) {
    // handle
    can_emu_service__on_packet_transferred();

    // prepare to receive the next packet
    usart_rx_thread__init();
}


USART_RX_THREAD_INTERRUPT {
    ST_YPLUS(usart0__getc());

    DEC(usart_rx_thread__size);
    IF_ZERO(usart_rx_thread__on_packet_transferred());
    RETI();    
}
