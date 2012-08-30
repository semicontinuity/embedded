#ifndef __COMM_SERVICE__DESCRIPTOR_MEMORY_H
#define __COMM_SERVICE__DESCRIPTOR_MEMORY_H

#include <string.h>
#include <avr/pgmspace.h>
#include "comm_service.h"
#include "cpu/avr/drivers/net/can/mcp251x/canp.h"


#define CANP_REPORT__CAN_READ       0x80
#define CANP_REPORT__FLASH_READ     0x90
#define CANP_REPORT__MEMORY_READ    0xA0
#define CANP_REPORT__RESET          0xFF


extern const uint8_t comm_sevice__descriptor_memory__value[] PROGMEM;

inline static void comm_service__descriptor_memory__handle(void) {
    // TODO: check OWNER bit
    if (CANP_RTR_BITS(comm_service__buffer.header)) {
        // Handle GET request
        uint8_t slot = CANP_SLOT_BITS(comm_service__buffer.header.id);
        // Do not check SLOT
        memcpy_P((void*)comm_service__buffer.data, comm_sevice__descriptor_memory__value + (slot << 3), comm_service__buffer.header.dlc);
        comm_service__send_response(slot, comm_service__buffer.header.dlc, (const uint8_t*)&comm_service__buffer.data);
    }
    // Ignore malformed requests
}

#endif