#ifndef __COMM_SERVICE__DESCRIPTOR_MEMORY_H
#define __COMM_SERVICE__DESCRIPTOR_MEMORY_H

#include <string.h>
#include <avr/pgmspace.h>
#include "comm_service.h"
#include "cpu/avr/drivers/net/can/mcp251x/canp.h"


extern const uint8_t comm_sevice__descriptor_memory__value[] PROGMEM;

inline static void comm_service__descriptor_memory__handle(const uint8_t request_type) {
    if (CANP_REQUEST_GET(request_type)) {
        // Handle GET request
        uint8_t slot = CANP_SLOT_BITS(comm_service__packet.header.id);
        uint8_t length = CANP_DATA_LENGTH_BITS(comm_service__packet.header);
        // Do not check SLOT
        memcpy_P((void*)comm_service__packet.data, comm_sevice__descriptor_memory__value + (slot << 3), length);
        comm_service__send_response(length, (const uint8_t*)&comm_service__packet.data);
    }
    // Ignore PUT requests
}

#endif