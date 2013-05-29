#ifndef __KERNEL__ADMIN_H
#define __KERNEL__ADMIN_H

#include <avr/pgmspace.h>
#include "cpu/avr/asm.h"
#include "cpu/avr/eeprom.h"
#include "cpu/avr/flash.h"
#include "cpu/avr/drivers/net/can/mcp251x/canp.h"
#include "cpu/avr/drivers/net/can/mcp251x/operations.h"

#include "descriptor.h"


#define CANP_REPORT__ADMIN          0xF8

#define CANP_REPORT__MEMORY_READ    0xF8
#define CANP_REPORT__MEMORY_WRITE   0xF9
#define CANP_REPORT__EEPROM_READ    0xFA
#define CANP_REPORT__EEPROM_WRITE   0xFB
#define CANP_REPORT__FLASH_READ     0xFC
#define CANP_REPORT__FLASH_WRITE    0xFD
#define CANP_REPORT__AUTH           0xFE
#define CANP_REPORT__MODE           0xFF


/**
 * Handle administrative interface requests.
 * All requests, handled here, are PUT requests.
 * (because queries contain extra parameters that must be transferred in the packet payload)
 */
static inline void kernel__admin__handle(void) {
    mcp251x_message_buffer* frame = &kernel__frame;
    FIX_POINTER_Y(frame);
    uint8_t* data = frame->data;
    uint16_t* wdata = (uint16_t*)(frame->data);

    switch (CANP_SLOT_BITS_FP(frame)) {
    case CANP_REPORT__MEMORY_READ:
        // Read data from memory (4 bytes).
        // Frame format:
        // TAG: memory id (0: kernel__status, 1: RAM)
        // Data [0..3]:   address; address[3] and address[2] must be 0.
        // DLC: must be 4
        {
            uint8_t length = frame->header.dlc;
            uint16_t w0 = *wdata;
            uint8_t a2 = frame->data[2];
            uint8_t a3 = frame->data[3];

            if (!(a2 | a3)) {
                if (length == 4) {
                    uint8_t* ptr = CANP_TAG_BITS_FP(frame) ? 0 : (uint8_t*)&kernel__status;
                    ptr += w0;

                    do { *data++ = *ptr++; } while (--length);
                    kernel__send_response(8, (const uint8_t*)frame);
                }
            }
        }
        break;
    case CANP_REPORT__MEMORY_WRITE:
        // Write data to memory.
        // Frame format:
        // TAG: memory id (0: kernel__status, 1: RAM)
        // Data [0..3]:   address; address[3] and address[2] must be 0.
        // Data [4..DLC]: data
        {
            uint8_t length = frame->header.dlc;
            uint16_t w0 = *wdata;
            uint8_t a2 = frame->data[2];
            uint8_t a3 = frame->data[3];

            if (!(a2 | a3)) {
                if (length -= 4) {
                    uint8_t* ptr = CANP_TAG_BITS_FP(frame) ? 0 : (uint8_t*)&kernel__status;
                    ptr += w0;
                    do { *ptr++ = *data++; } while (--length);
                }
            }
        }
        break;
    case CANP_REPORT__EEPROM_READ:
        // Read 4 bytes of EEPROM memory, given the address in data[0..3]
        {
            uint8_t length = frame->header.dlc;
            uint16_t w0 = *wdata;
            uint8_t a2 = frame->data[2];
            uint8_t a3 = frame->data[3];

            if (!(a2 | a3)) {
                if (length == 4) {
                    kernel__read_eeprom_block(&kernel__frame.data[4], (void*)w0, 4);
                    kernel__send_response(8, (const uint8_t*)frame);
                }
            }
        }
        break;
    case CANP_REPORT__EEPROM_WRITE:
        // Write 1..4 bytes of EEPROM memory, given the address in data[0..3]
        // Can take a long time to disrupt the device operation,
        // so write EEPROM only when the device is not performing any time-critical tasks.
        {
            uint8_t length = frame->header.dlc;
            uint16_t w0 = *wdata;
            uint8_t a2 = frame->data[2];
            uint8_t a3 = frame->data[3];

            if (!(a2 | a3)) {
                if (length -= 4) {
                    kernel__write_eeprom_block((void*)w0, &kernel__frame.data[4], length);
                }
            }
        }
        break;
    case CANP_REPORT__FLASH_READ:
        {
            // Read 32 bits of memory, given the address in data[0..3]
            uint8_t length = frame->header.dlc;
            uint16_t w0 = *wdata;
            uint8_t a2 = frame->data[2];
            uint8_t a3 = frame->data[3];

            if (!(a2 | a3)) {
                if (length == 4) {
                    if (!CANP_TAG_BITS_FP(frame)) {
                        uint16_t offset_address = DESCRIPTOR__ADDRESS;
                        uint16_t offset = __LPM_word__(offset_address);
                        w0 += offset;
                    }
                    frame->data[4] = __LPM_increment__(w0);
                    frame->data[5] = __LPM_increment__(w0);
                    frame->data[6] = __LPM_increment__(w0);
                    frame->data[7] = __LPM_increment__(w0);
                    kernel__send_response(8, (const uint8_t*)frame);
                }
            }
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
        {
            uint8_t a2 = frame->data[2];
            uint8_t a3 = frame->data[3];

            if (!(a2 | a3)) {
                // optimize
                asm ("push r0");
                asm ("push r1");

                asm ("mov r0, %0" ::"r"(frame->data[6]):"r0");
                asm ("mov r1, %0" ::"r"(frame->data[7]):"r1");
                asm ("mov r30, %0" ::"r"(frame->data[0]):"r30");
                asm ("mov r31, %0" ::"r"(frame->data[1]):"r31");
                FLASH__REGISTER = frame->data[4];

                asm ("spm");

                asm ("pop r1");
                asm ("pop r0");
            }
        }
        break;
    case CANP_REPORT__AUTH:
        break;
    case CANP_REPORT__MODE:
        // DLC and value not checked.
        kernel__mode__set(kernel__frame.data[0]);
        // Executed in context of the interrupt, so interrupts are disabled. Safe to perform soft reset.
        asm("jmp __vectors");
    }
}

#endif