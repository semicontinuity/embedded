#ifndef __COMM_SERVICE__DESCRIPTOR_MEMORY_H
#define __COMM_SERVICE__DESCRIPTOR_MEMORY_H

#include <string.h>
#include <avr/pgmspace.h>
#include "kernel.h"
#include "cpu/avr/drivers/net/can/mcp251x/canp.h"
#include "cpu/avr/util/memory.h"


extern const uint8_t comm_sevice__descriptor_memory__value[] PROGMEM;

inline static void comm_service__descriptor_memory__handle(const uint8_t is_get) {
    if (is_get) {
        uint8_t slot = CANP_SLOT_BITS(comm_service__packet.header.id);
        uint8_t length = CANP_DATA_LENGTH_BITS(comm_service__packet.header);
        // Do not check SLOT

        // Same as memcpy_P, but inlined and produces less stupid code. Still some stuped register moves, but does not use r28
        memory__copy_P((void*)comm_service__packet.data, (const void* PROGMEM)comm_sevice__descriptor_memory__value + (slot << 3), length);
        comm_service__send_response(length, (const uint8_t*)&comm_service__packet.data);
    }
    // Ignore PUT requests
}

#endif