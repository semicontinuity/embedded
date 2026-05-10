#ifndef __KERNEL__ADMIN_H
#define __KERNEL__ADMIN_H

#include <avr/pgmspace.h>
#include "cpu/avr/eeprom.h"
#include "cpu/avr/flash.h"
#include "cpu/avr/drivers/net/can/mcp251x/canp.h"
#include "cpu/avr/drivers/net/can/mcp251x/operations.h"
#include "drivers/out/mcp251x_select.h"


#define CANP_REPORT__ADMIN          0xF0

#define CANP_REPORT__MEMORY_READ    0xF0
#define CANP_REPORT__MEMORY_WRITE   0xF1
#define CANP_REPORT__EEPROM_READ    0xF2
#define CANP_REPORT__EEPROM_WRITE   0xF3
#define CANP_REPORT__CAN_READ       0xF8
#define CANP_REPORT__CAN_WRITE      0xF9
#define CANP_REPORT__FLASH_READ     0xFA
#define CANP_REPORT__FLASH_WRITE    0xFB
#define CANP_REPORT__STATS_READ     0xFC
#define CANP_REPORT__STATS_WRITE    0xFD
#define CANP_REPORT__STOP           0xFE
#define CANP_REPORT__RESET          0xFF


/**
 * Handle administrative interface requests.
 * All requests, handled here, are PUT requests.
 * (because queries contain extra parameters that must be transferred in the packet payload)
 */
static inline void kernel__admin__handle(void) {
    switch (CANP_SLOT_BITS(kernel__frame.header.id)) {
    case CANP_REPORT__MEMORY_READ:
        // Read 32 bits of memory, given the address in data[0..3]
        if (kernel__frame.data[3] == 0 && kernel__frame.data[2] == 0) {
            const uint8_t* ptr = (const uint8_t*)(kernel__frame.data[0] | (kernel__frame.data[1] << 8));
            kernel__frame.data[4] = ptr[0];
            kernel__frame.data[5] = ptr[1];
            kernel__frame.data[6] = ptr[2];
            kernel__frame.data[7] = ptr[3];
            kernel__send_response(8, (const uint8_t*)&kernel__frame.data);
        }
        break;
    case CANP_REPORT__MEMORY_WRITE:
        // Write 8 bits of memory, given the address in data[0..3] and data in [4]
        if (kernel__frame.data[3] == 0 && kernel__frame.data[2] == 0) {
            uint8_t* ptr = (uint8_t*)(kernel__frame.data[0] | (kernel__frame.data[1] << 8));
            *ptr = kernel__frame.data[4];
        }
        break;

    case CANP_REPORT__EEPROM_READ:
        // Read 4 bytes of EEPROM memory, given the address in data[0..3]
        {
            uint8_t length = kernel__frame.header.dlc;
            if (length == 4 && kernel__frame.data[3] == 0 && kernel__frame.data[2] == 0) {
                uint8_t* ptr = (uint8_t*)(kernel__frame.data[0] | (kernel__frame.data[1] << 8));
                kernel__frame.data[4] = eeprom__read_byte(ptr);
                ptr += 1;
                kernel__frame.data[5] = eeprom__read_byte(ptr);
                ptr += 1;
                kernel__frame.data[6] = eeprom__read_byte(ptr);
                ptr += 1;
                kernel__frame.data[7] = eeprom__read_byte(ptr);
                kernel__send_response(8, (const uint8_t*)&kernel__frame.data);
            }
        }
        break;
    case CANP_REPORT__EEPROM_WRITE:
        // Write 1..4 bytes of EEPROM memory, given the address in data[0..3]
        // Can take a long time to disrupt the device operation,
        // so write EEPROM only when the device is not performing any time-critical tasks.
        {
            uint8_t length = kernel__frame.header.dlc;
            if ((length -= 4) > 0 && kernel__frame.data[3] == 0 && kernel__frame.data[2] == 0) {
                uint8_t *r_ptr = (uint8_t*)(&kernel__frame.data[4]);
                uint8_t *w_ptr = (uint8_t*)(kernel__frame.data[0] | (kernel__frame.data[1] << 8));
                do {
                    eeprom__write_byte(w_ptr++, *r_ptr++);
                }
                while (--length > 0);
            }
        }
        break;
    case CANP_REPORT__CAN_READ:
        // DLC ignored.
        // Read a CAN register, given the address in data[0]
        if (kernel__frame.data[3] == 0 && kernel__frame.data[2] == 0 && kernel__frame.data[1] == 0) {
            kernel__frame.data[4] = mcp251x__read(kernel__frame.data[0]);
            kernel__send_response(5, (const uint8_t*)&kernel__frame.data);
        }
        break;
    case CANP_REPORT__CAN_WRITE:
        // DLC ignored.
        // Write  8 bits of memory, given the address in data[0]
        if (kernel__frame.data[3] == 0 && kernel__frame.data[2] == 0 && kernel__frame.data[1] == 0) {
            mcp251x__write(kernel__frame.data[0], kernel__frame.data[4]);
        }
        break;
    case CANP_REPORT__STATS_READ:
        kernel__send_response(8, (const uint8_t*)&kernel__status);
        break;
    case CANP_REPORT__STATS_WRITE:
        {
            uint8_t* r_ptr = (uint8_t*)(&kernel__frame.data);
            uint8_t* w_ptr = (uint8_t*)(&kernel__status);
            for (int8_t c = 7; c >= 0; c--) *w_ptr++ = *r_ptr++;
        }
        break;
    case CANP_REPORT__FLASH_READ:
        // Read 32 bits of memory, given the address in data[0..3]
        if (kernel__frame.data[3] == 0 && kernel__frame.data[2] == 0) {
            const uint8_t* PROGMEM ptr = (const uint8_t* PROGMEM)(kernel__frame.data[0] | (kernel__frame.data[1] << 8));
            kernel__frame.data[4] = pgm_read_byte(ptr + 0);
            kernel__frame.data[5] = pgm_read_byte(ptr + 1);
            kernel__frame.data[6] = pgm_read_byte(ptr + 2);
            kernel__frame.data[7] = pgm_read_byte(ptr + 3);
            kernel__send_response(8, (const uint8_t*)&kernel__frame.data);
        }
        break;
    case CANP_REPORT__FLASH_WRITE:
        // Flash programming
        // Data format:
        // [0..1] address -> Z
        // [2..3] must be 0
        // [4]    value for SPMCSR
        // [5]    must be 0
        // [6..7] data ->r0:r1
        if (kernel__frame.data[3] == 0 && kernel__frame.data[2] == 0) {
            // optimize
            asm ("push r0");
            asm ("push r1");

            asm ("mov r0, %0" ::"r"(kernel__frame.data[6]):"r0");
            asm ("mov r1, %0" ::"r"(kernel__frame.data[7]):"r1");
            asm ("mov r30, %0" ::"r"(kernel__frame.data[3]):"r30");
            asm ("mov r31, %0" ::"r"(kernel__frame.data[1]):"r31");
            FLASH__REGISTER = kernel__frame.data[4];

            asm ("spm");

            asm ("pop r1");
            asm ("pop r0");
        }
        break;
    case CANP_REPORT__STOP:
        kernel__mode__set();
        // Executed in context of the interrupt, so interrupts are disabled. Safe to perform soft reset.
        asm("jmp __vectors");
    case CANP_REPORT__RESET:
        kernel__mode__clear();
        // Executed in context of the interrupt, so interrupts are disabled. Safe to perform soft reset.
        asm("jmp __vectors");
    }
}

#endif