#ifndef __KERNEL__ADMIN_H
#define __KERNEL__ADMIN_H

#include <avr/pgmspace.h>
#include "cpu/avr/eeprom.h"
#include "cpu/avr/drivers/net/can/mcp251x/canp.h"
#include "cpu/avr/drivers/net/can/mcp251x/operations.h"
#include "can_selector.h"


#define CANP_REPORT__MEMORY_READ    0xF0
#define CANP_REPORT__MEMORY_WRITE   0xF1
#define CANP_REPORT__EEPROM_READ    0xF2
#define CANP_REPORT__EEPROM_WRITE   0xF3
#define CANP_REPORT__CAN_READ       0xF8
#define CANP_REPORT__CAN_WRITE      0xF9
#define CANP_REPORT__FLASH_READ     0xFA
#define CANP_REPORT__FLASH_WRITE    0xFB
#define CANP_REPORT__STOP           0xFE
#define CANP_REPORT__RESET          0xFF


/**
 * Handle administrative interface requests.
 * All requests, handled here, are PUT requests.
 * (because queries contain extra parameters that must be transferred in the packet payload)
 */
static inline void kernel__admin__handle(void) {
    switch (CANP_SLOT_BITS(comm_service__packet.header.id)) {
    case CANP_REPORT__MEMORY_READ:
        // Read 32 bits of memory, given the address in data[0..3]
        if (comm_service__packet.data[3] == 0 && comm_service__packet.data[2] == 0) {
            const uint8_t* ptr = (const uint8_t*)(comm_service__packet.data[0] | (comm_service__packet.data[1] << 8));
            comm_service__packet.data[4] = ptr[0];
            comm_service__packet.data[5] = ptr[1];
            comm_service__packet.data[6] = ptr[2];
            comm_service__packet.data[7] = ptr[3];
            comm_service__send_response(8, (const uint8_t*)&comm_service__packet.data);
        }
        break;
    case CANP_REPORT__EEPROM_READ:
        // Read 4 bytes of EEPROM memory, given the address in data[0..3]
        {
            uint8_t length = comm_service__packet.header.dlc;
            if (length == 4 && comm_service__packet.data[3] == 0 && comm_service__packet.data[2] == 0) {
                uint8_t* ptr = (uint8_t*)(comm_service__packet.data[0] | (comm_service__packet.data[1] << 8));
                comm_service__packet.data[4] = eeprom__read_byte(ptr);
                ptr += 1;
                comm_service__packet.data[5] = eeprom__read_byte(ptr);
                ptr += 1;
                comm_service__packet.data[6] = eeprom__read_byte(ptr);
                ptr += 1;
                comm_service__packet.data[7] = eeprom__read_byte(ptr);
                comm_service__send_response(8, (const uint8_t*)&comm_service__packet.data);
            }
        }
        break;
    case CANP_REPORT__EEPROM_WRITE:
        // Write 1..4 bytes of EEPROM memory, given the address in data[0..3]
        // Can take a long time to disrupt the device operation,
        // so write EEPROM only when the device is not performing any time-critical tasks.
        {
            uint8_t length = comm_service__packet.header.dlc;
            if ((length -= 4) > 0 && comm_service__packet.data[3] == 0 && comm_service__packet.data[2] == 0) {
                uint8_t *r_ptr = (uint8_t*)(&comm_service__packet.data[4]);
                uint8_t *w_ptr = (uint8_t*)(comm_service__packet.data[0] | (comm_service__packet.data[1] << 8));
                do {
                    eeprom__write_byte(w_ptr++, *r_ptr++);
                }
                while (--length > 0);
            }
        }
        break;
    case CANP_REPORT__CAN_READ:
        // DLC ignored.
        // Read 8 bits of memory, given the address in data[0]
        if (comm_service__packet.data[3] == 0 && comm_service__packet.data[2] == 0 && comm_service__packet.data[1] == 0) {
            can_selector__run(comm_service__packet.data[4] = mcp251x_read_byte(comm_service__packet.data[0]));
            comm_service__send_response(5, (const uint8_t*)&comm_service__packet.data);
        }
        break;
    case CANP_REPORT__FLASH_READ:
        // Read 32 bits of memory, given the address in data[0..3]
        if (comm_service__packet.data[3] == 0 && comm_service__packet.data[2] == 0) {
            const uint8_t* PROGMEM ptr = (const uint8_t* PROGMEM)(comm_service__packet.data[0] | (comm_service__packet.data[1] << 8));
            comm_service__packet.data[4] = pgm_read_byte(ptr + 0);
            comm_service__packet.data[5] = pgm_read_byte(ptr + 1);
            comm_service__packet.data[6] = pgm_read_byte(ptr + 2);
            comm_service__packet.data[7] = pgm_read_byte(ptr + 3);
            comm_service__send_response(8, (const uint8_t*)&comm_service__packet.data);
        }
        break;
    case CANP_REPORT__STOP:
        MCUSR = 0x0F;
    case CANP_REPORT__RESET:
        // Executed in context of the interrupt, so interrupts are disabled.
        asm("rjmp __vectors");
    }
}

#endif