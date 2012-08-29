#ifndef __COMM_SERVICE__ADMIN_HANDLER_H
#define __COMM_SERVICE__ADMIN_HANDLER_H

#include <avr/pgmspace.h>
#include "cpu/avr/drivers/net/can/mcp251x/canp.h"
#include "cpu/avr/drivers/net/can/mcp251x/operations.h"
#include "can_selector.h"


#define CANP_REPORT__CAN_READ       0x80
#define CANP_REPORT__FLASH_READ     0x90
#define CANP_REPORT__MEMORY_READ    0xA0
#define CANP_REPORT__RESET          0xFF


static inline void comm_service__handle__admin(void) {
    // TODO check for message type
    switch (CANP_SLOT_BITS(comm_service__buffer.header.id)) {
    case CANP_REPORT__CAN_READ:
        // Read 32 bits of memory, given the address in data[0..3]
        if (comm_service__buffer.data[3] == 0 && comm_service__buffer.data[2] == 0 && comm_service__buffer.data[1] == 0) {
            can_selector__run(comm_service__buffer.data[4] = mcp251x_read_byte(comm_service__buffer.data[0]));
            comm_service__send_response(CANP_REPORT__CAN_READ, 8, (const uint8_t*)&comm_service__buffer.data);
        }
        break;
    case CANP_REPORT__FLASH_READ:
        // Read 32 bits of memory, given the address in data[0..3]
        if (comm_service__buffer.data[3] == 0 && comm_service__buffer.data[2] == 0) {
            const uint8_t* PROGMEM ptr = (const uint8_t* PROGMEM)(comm_service__buffer.data[0] | (comm_service__buffer.data[1] << 8));
            comm_service__buffer.data[4] = pgm_read_byte(ptr + 0);
            comm_service__buffer.data[5] = pgm_read_byte(ptr + 1);
            comm_service__buffer.data[6] = pgm_read_byte(ptr + 2);
            comm_service__buffer.data[7] = pgm_read_byte(ptr + 3);
            comm_service__send_response(CANP_REPORT__FLASH_READ, 8, (const uint8_t*)&comm_service__buffer.data);
        }
        break;
    case CANP_REPORT__MEMORY_READ:
        // Read 32 bits of memory, given the address in data[0..3]
        if (comm_service__buffer.data[3] == 0 && comm_service__buffer.data[2] == 0) {
            const uint8_t* ptr = (const uint8_t*)(comm_service__buffer.data[0] | (comm_service__buffer.data[1] << 8));
            comm_service__buffer.data[4] = ptr[0];
            comm_service__buffer.data[5] = ptr[1];
            comm_service__buffer.data[6] = ptr[2];
            comm_service__buffer.data[7] = ptr[3];
            comm_service__send_response(CANP_REPORT__MEMORY_READ, 8, (const uint8_t*)&comm_service__buffer.data);
        }
        break;
    case CANP_REPORT__RESET:
        // Executed in context of the interrupt, so interrupts are disabled.
        ((void (*) (void)) 0) ();
        break;
    }
}

#endif