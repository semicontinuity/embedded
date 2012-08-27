#ifndef __COMM_SERVICE__COMMAND_HANDLER_H
#define __COMM_SERVICE__COMMAND_HANDLER_H

#include <avr/pgmspace.h>

#define COMMAND__MEMORY_READ    ('m')

static inline void comm_service__handle__commands(void) {
    switch (CANP_SLOT_BITS(comm_service__buffer.header.id)) {
    case COMMAND__MEMORY_READ:
        // Read 32 bits of memory, given the address in data[0..3]
        if (comm_service__buffer.data[3] == 0 && comm_service__buffer.data[2] == 0) {
            const uint8_t* PROGMEM ptr = (const uint8_t* PROGMEM)(comm_service__buffer.data[0] | (comm_service__buffer.data[1] << 8));
            comm_service__buffer.data[4] = ptr[0];
            comm_service__buffer.data[5] = ptr[1];
            comm_service__buffer.data[6] = ptr[2];
            comm_service__buffer.data[7] = ptr[3];
            comm_service__send_response(COMMAND__MEMORY_READ, 8, (const uint8_t*)&comm_service__buffer.data);
        }
        break;
    }
}

#endif