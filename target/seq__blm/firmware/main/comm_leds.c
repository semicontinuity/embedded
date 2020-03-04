// =============================================================================
// Receives 4-byte messages via I2C with color data.
// Datagram format: {button index: 1 byte + 3-byte color value}
// =============================================================================

#include <cpu/avr/twi.h>
#include "twi_slave_callbacks.h"

#include "leds.h"
#include "util/bitops.h"

#include <drivers/out/alarm.h>
#include <drivers/out/led_a.h>
#include <drivers/out/led_b.h>



#ifdef COMM_LEDS__MEMORY__PTR__REG
register volatile uint8_t* comm_leds__memory__ptr asm(QUOTE(COMM_LEDS__MEMORY__PTR__REG));
#else
volatile uint8_t* comm_leds__memory__ptr;
#endif

#ifdef COMM_LEDS__HEADER__REG
register volatile uint8_t comm_leds__header asm(QUOTE(COMM_LEDS__HEADER__REG));
#else
volatile uint8_t comm_leds__header;
#endif

#if defined(COMM_LEDS__HEADER_RECEIVED__HOST) && defined(COMM_LEDS__HEADER_RECEIVED__BIT)
DEFINE_BITVAR(comm_leds__header_received, COMM_LEDS__HEADER_RECEIVED__HOST, COMM_LEDS__HEADER_RECEIVED__BIT);
#else
volatile uint8_t comm_leds__header_received;
DEFINE_BITVAR(comm_leds__header_received, comm_leds__header_received, 0);
#endif

#if defined(COMM_LEDS__HEADER_PARSED__HOST) && defined(COMM_LEDS__HEADER_PARSED__BIT)
DEFINE_BITVAR(comm_leds__header_parsed, COMM_LEDS__HEADER_PARSED__HOST, COMM_LEDS__HEADER_PARSED__BIT);
#else
volatile uint8_t comm_leds__header_parsed;
DEFINE_BITVAR(comm_leds__header_parsed, comm_leds__header_parsed, 0);
#endif


// TWI Slave callbacks
// -----------------------------------------------------------------------------

void twi__slave__on_data_reception_started(void) {
    __asm__ __volatile__("twi__slave__on_data_reception_started:");
    twi__continue(true, false);
    comm_leds__header = 0;
    comm_leds__header_parsed__set(0);
}

void twi__slave__on_data_byte_received(const uint8_t value) {
    __asm__ __volatile__("twi__slave__on_data_byte_received:");
    twi__continue(true, false);

    if (comm_leds__header_received__get()) {
        // Received payload byte of multi-byte message.
        // comm_leds__header contains first byte of multi-byte message.
        if (!comm_leds__header_parsed__get()) {
            comm_leds__header_parsed__set(1);
            if (comm_leds__header & 0x80U) {
                // WRITE_PALETTE message, format [1][palette index]
                uint8_t palette_index = comm_leds__header & 0x7FU;
                comm_leds__memory__ptr = leds__palette + (palette_index + palette_index + palette_index);
            } else {
                if (comm_leds__header & 0x40U) {
                    // UNPACK128 message, format [ 01 ] [RESERVED1: 1] [ REFRESH : 1] [ LED : 4] + [ RESERVED2: 1] [ INDEX : 7 ]
                    return;
                } else {
                    // WRITE_VMEM message, format [ 00 ] [ DIR: 1] [ REFRESH: 1] [ START_LED : 4] + [ 3-byte color value ]+
                    uint8_t led_index = comm_leds__header & 0x0FU;
                    comm_leds__memory__ptr = leds__palette + (led_index + led_index + led_index);
                }
            }
        }

        // optimize it
        *comm_leds__memory__ptr++ = value;
    } else {
        comm_leds__header_received__set(1);
        comm_leds__header = value;
    }
}


void twi__slave__on_data_reception_finished(void) {
    __asm__ __volatile__("twi__slave__on_data_reception_finished:");
    twi__continue(true, false);

    if (comm_leds__header_received__get()) {
        comm_leds__header_received__set(0);

        if (comm_leds__header_parsed__get()) {
            // Multi-byte messages
            comm_leds__header_parsed__set(0);

            if (!(comm_leds__header & 0x80U)) {
                // WRITE_VMEM or UNPACK128
                if (comm_leds__header & 0x10U) {
                    leds__refresh();
                }
            }
        } else {
            // 1-byte message, stored in comm_leds__header => type PACKED4, format [ DIR: 1 ] [ POS : 2] [ CHANNEL: 1] [ PATTERN : 4]
            leds__refresh();
        }
    } else {
        // Empty message => RESET
        leds__refresh();
    }
}
