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
#include <cpu/avr/asm.h>


#ifdef COMM_LEDS__SELECTORS__PTR__REG
register volatile uint8_t* comm_leds__selectors__ptr asm(QUOTE(COMM_LEDS__SELECTORS__PTR__REG));
#else
volatile uint8_t* comm_leds__selectors__ptr;
#endif

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


uint8_t comm_leds__selectors__get(void) {
#if defined(COMM_LEDS__SELECTORS__PTR__REG) && COMM_LEDS__SELECTORS__PTR__REG==28
    return LOAD_Y_OFFSET(comm_leds__selectors__ptr, 0);
#elif defined(COMM_LEDS__SELECTORS__PTR__REG) && COMM_LEDS__SELECTORS__PTR__REG==30
    return LOAD_Z_OFFSET(comm_leds__selectors__ptr, 0);
#else
    return *comm_leds__selectors__ptr;
#endif
}

void comm_leds__selectors__write(const uint8_t value) {
#if defined(COMM_LEDS__SELECTORS__PTR__REG) && COMM_LEDS__SELECTORS__PTR__REG==28
    STORE_YPLUS(comm_leds__selectors__ptr, value);
#elif defined(COMM_LEDS__SELECTORS__PTR__REG) && COMM_LEDS__SELECTORS__PTR__REG==30
    STORE_ZPLUS(comm_leds__selectors__ptr, value);
#else
    *comm_leds__selectors__ptr++ = value;
#endif
}

uint8_t *comm_leds__palette__position(const uint8_t position) {
    return leds__palette + ((uint8_t)(position + position) + position);
}


void comm_leds__data__write(const uint8_t value) {
#if defined(COMM_LEDS__MEMORY__PTR__REG) && COMM_LEDS__MEMORY__PTR__REG==26
    STORE_XPLUS(comm_leds__memory__ptr, value);
#elif defined(COMM_LEDS__MEMORY__PTR__REG) && COMM_LEDS__MEMORY__PTR__REG==28
    STORE_YPLUS(comm_leds__memory__ptr, value);
#elif defined(COMM_LEDS__MEMORY__PTR__REG) && COMM_LEDS__MEMORY__PTR__REG==30
    STORE_ZPLUS(comm_leds__memory__ptr, value);
#else
    *comm_leds__memory__ptr++ = value;
#endif
}


void copy_color_from_palette(uint8_t index) {
    uint8_t *palette_position = comm_leds__palette__position(index);
    comm_leds__data__write(LOAD_XPLUS(palette_position));
    comm_leds__data__write(LOAD_XPLUS(palette_position));
    comm_leds__data__write(LOAD_XPLUS(palette_position));
}


// TWI Slave callbacks
// -----------------------------------------------------------------------------

void twi__slave__on_data_reception_started(void) {
    __asm__ __volatile__("twi__slave__on_data_reception_started:");
    twi__continue(true, false);
    comm_leds__header_received__set(0);
    comm_leds__header_parsed__set(0);
}

void twi__slave__on_data_byte_received(const uint8_t value) {
    __asm__ __volatile__("twi__slave__on_data_byte_received:");

    if (comm_leds__header_received__get()) {
        // Received payload byte of multi-byte message.
        // comm_leds__header contains first byte of multi-byte message.

        if (comm_leds__header & 0x80U) {
            // WRITE_PALETTE message, format [1][palette index]
            if (!comm_leds__header_parsed__get()) {
                comm_leds__header_parsed__set(1);
                uint8_t palette_index = comm_leds__header & 0x7FU;
                comm_leds__memory__ptr = leds__palette + (palette_index + palette_index + palette_index);
            }
            // optimize it
            *comm_leds__memory__ptr++ = value;
        } else {
            // bit 6 is 1 for UNPACK128 message, 0 for WRITE_VMEM
            if (comm_leds__header & 0x40U) {        // is UNPACK128?
                // UNPACK128 message, format [ 01 ] [DIR : 1] [ REFRESH : 1] [ LED : 4] + [ RESERVED: 1] [ INDEX : 7 ]
                __asm__ __volatile__("twi__slave__on_data_reception_finished__unpack128__init:");
                if (!comm_leds__header_parsed__get()) {
                    comm_leds__header_parsed__set(1);
                    uint8_t led_index = comm_leds__header & 0x0FU;  // extract LED field
                    comm_leds__selectors__ptr = leds__selectors + led_index;
                    comm_leds__memory__ptr = leds__data + ((uint8_t)(led_index + led_index) + led_index);
                }

                __asm__ __volatile__("twi__slave__on_data_reception_finished__unpack128__write_selector:");
                comm_leds__selectors__write(value);
                if (comm_leds__header & 0x20U) {    // DIR bit set?
                    comm_leds__selectors__ptr += 3; // point to the selector of LED below
                }

                __asm__ __volatile__("twi__slave__on_data_reception_finished__unpack128__write_vmem:");
                uint8_t *color_ptr = leds__palette + (value + value + value);   // value is INDEX field, assume RESERVED is 0
                comm_leds__data__write(*color_ptr++);
                comm_leds__data__write(*color_ptr++);
                comm_leds__data__write(*color_ptr);
                if (comm_leds__header & 0x20U) {    // DIR bit set?
                    comm_leds__memory__ptr += 9;    // point to the memory of LED below
                }
            } else {
                // WRITE_VMEM message, format [ 00 ] [ DIR: 1] [ REFRESH: 1] [ START_LED : 4] + [ 3-byte color value ]+
                __asm__ __volatile__("twi__slave__on_data_reception_finished__write_vmem__init:");
                if (!comm_leds__header_parsed__get()) {
                    comm_leds__header_parsed__set(1);
                    uint8_t led_index = comm_leds__header & 0x0FU;  // extract START_LED field
                    comm_leds__memory__ptr = leds__data + (led_index + led_index + led_index);
                }

                __asm__ __volatile__("twi__slave__on_data_reception_finished__write_vmem:");
                comm_leds__data__write(value);
                if (comm_leds__header & 0x20U) {    // DIR bit set?
                    comm_leds__memory__ptr += 9;    // point to the memory of LED below
                }
            }
        }
    } else {
        __asm__ __volatile__("twi__slave__on_data_reception_finished__received_header:");
        comm_leds__header_received__set(1);
        comm_leds__header = value;
    }
    __asm__ __volatile__("twi__slave__on_data_reception_finished__exit:");
    twi__continue(true, false);
}


uint8_t modify_indexed_color(uint8_t color_index, uint8_t pattern_mask, uint8_t mask) {
    color_index &= (uint8_t) ~mask;                    // clear bit of selected CHANNEL
    if (comm_leds__header & pattern_mask)               // bit X of PATTERN set?
        color_index |= mask;                           // set bit of selected CHANNEL
    return color_index;
}


void twi__slave__on_data_reception_finished(void) {
    __asm__ __volatile__("twi__slave__on_data_reception_finished:");

    if (comm_leds__header_received__get()) {
        comm_leds__header_received__set(0);

        if (comm_leds__header_parsed__get()) {
            // Multi-byte messages
            comm_leds__header_parsed__set(0);

            if (!(comm_leds__header & 0x80U)) {     // not WRITE_PALETTE?
                // WRITE_VMEM or UNPACK128
                if (comm_leds__header & 0x10U) {    // bit 4 is REFRESH, is it set?
                    leds__refresh__set(1);
                }
            }
        } else {
            // 1-byte message, stored in comm_leds__header => type PACKED4, format [ CHANNEL: 1 ] [ POS : 2] [ DIR: 1 ] [ PATTERN : 4]
            // first, updates one of two lowest bits of selector memory entry,
            // then fetches 24-bit color value from the corresponding palette entry,
            // writes the color to the corresponding position of the video memory,
            // and finally, requests the LEDs refresh.
            comm_leds__selectors__ptr = leds__selectors;
            comm_leds__memory__ptr = leds__data;
            uint8_t mask = 0x01U;                   // mask for CHANNEL 0
            if (comm_leds__header & 0x80U)          // CHANNEL 1?
                mask = 0x02U;                       // mask for CHANNEL 1

            if (comm_leds__header & 0x10U) {        // vertical
                __asm__ __volatile__("twi__slave__on_data_reception_finished__packed4_v:");
                if (comm_leds__header & 0x40U)      // right half?
                    comm_leds__selectors__ptr += 2; // offset by 2 LEDs
                if (comm_leds__header & 0x40U)      // right half?
                    comm_leds__memory__ptr += 3*2;  // offset by 2 LEDs
                if (comm_leds__header & 0x20U)      // odd columns?
                    comm_leds__selectors__ptr += 1; // offset by 1 LEDs
                if (comm_leds__header & 0x20U)      // odd columns?
                    comm_leds__memory__ptr += 3*1;  // offset by 1 LEDs


                __asm__ __volatile__("twi__slave__on_data_reception_finished__packed4_v0p:");
                uint8_t color0_index = comm_leds__selectors__get(); // load indexed color for the current LED
                color0_index = modify_indexed_color(color0_index, 0x01U, mask);
                comm_leds__selectors__write(color0_index);          // store indexed color for the current LED
                comm_leds__selectors__ptr += 3;                     // select next LED (below current one)

                __asm__ __volatile__("twi__slave__on_data_reception_finished__packed4_v0c:");
                copy_color_from_palette(color0_index);
                comm_leds__memory__ptr += 9;                // point to the video memory of the next LED (below current one)


                __asm__ __volatile__("twi__slave__on_data_reception_finished__packed4_v1p:");
                uint8_t color1_index = comm_leds__selectors__get(); // load indexed color for the current LED
                color1_index = modify_indexed_color(color1_index, 0x02U, mask);
                comm_leds__selectors__write(color1_index);          // store indexed color for the current LED
                comm_leds__selectors__ptr += 3;                     // select next LED (below current one)

                __asm__ __volatile__("twi__slave__on_data_reception_finished__packed4_v1c:");
                copy_color_from_palette(color1_index);
                comm_leds__memory__ptr += 9;                // point to the video memory of the next LED (below current one)


                __asm__ __volatile__("twi__slave__on_data_reception_finished__packed4_v2p:");
                uint8_t color2_index = comm_leds__selectors__get(); // load indexed color for the current LED
                color2_index  = modify_indexed_color(color2_index, 0x04U, mask);
                comm_leds__selectors__write(color2_index);          // store indexed color for the current LED
                comm_leds__selectors__ptr += 3;                     // select next LED (below current one)

                __asm__ __volatile__("twi__slave__on_data_reception_finished__packed4_v2c:");
                copy_color_from_palette(color2_index);
                comm_leds__memory__ptr += 9;                // point to the video memory of the next LED (below current one)


                __asm__ __volatile__("twi__slave__on_data_reception_finished__packed4_v3p:");
                uint8_t color3_index = comm_leds__selectors__get(); // load indexed color for the current LED
                color3_index = modify_indexed_color(color3_index, 0x08U, mask);
                comm_leds__selectors__write(color3_index);          // store indexed color for the current LED

                __asm__ __volatile__("twi__slave__on_data_reception_finished__packed4_v3c:");
                copy_color_from_palette(color3_index);
            } else {                                // horizontal
                __asm__ __volatile__("twi__slave__on_data_reception_finished__packed4_h:");
                if (comm_leds__header & 0x40U)      // lower 2 rows?
                    comm_leds__selectors__ptr += 8; // offset by 8 LEDs
                if (comm_leds__header & 0x40U)      // lower 2 rows?
                    comm_leds__memory__ptr += 3*8;  // offset by 8 LEDs
                if (comm_leds__header & 0x20U)      // odd rows?
                    comm_leds__selectors__ptr += 4; // offset by 4 LEDs
                if (comm_leds__header & 0x20U)      // odd rows?
                    comm_leds__memory__ptr += 3*4;  // offset by 4 LEDs


                __asm__ __volatile__("twi__slave__on_data_reception_finished__packed4_h0p:");
                uint8_t color0_index = comm_leds__selectors__get(); // load indexed color for the current LED
                color0_index = modify_indexed_color(color0_index, 0x01U, mask);
                comm_leds__selectors__write(color0_index);          // store indexed color for the current LED and select next LED

                __asm__ __volatile__("twi__slave__on_data_reception_finished__packed4_h0c:");
                copy_color_from_palette(color0_index);

                __asm__ __volatile__("twi__slave__on_data_reception_finished__packed4_h1p:");
                uint8_t color1_index = comm_leds__selectors__get(); // load indexed color for the current LED
                color1_index = modify_indexed_color(color1_index, 0x02U, mask);
                comm_leds__selectors__write(color1_index);          // store indexed color for the current LED and select next LED

                __asm__ __volatile__("twi__slave__on_data_reception_finished__packed4_h1c:");
                copy_color_from_palette(color1_index);

                __asm__ __volatile__("twi__slave__on_data_reception_finished__packed4_h2p:");
                uint8_t color2_index = comm_leds__selectors__get(); // load indexed color for the current LED
                color2_index = modify_indexed_color(color2_index, 0x04U, mask);
                comm_leds__selectors__write(color2_index);          // load indexed color for the current LED and select next LED

                __asm__ __volatile__("twi__slave__on_data_reception_finished__packed4_h2c:");
                copy_color_from_palette(color2_index);

                __asm__ __volatile__("twi__slave__on_data_reception_finished__packed4_h3p:");
                uint8_t color3_index = comm_leds__selectors__get(); // load indexed color for the current LED
                color3_index = modify_indexed_color(color3_index, 0x08U, mask);
                comm_leds__selectors__write(color3_index);          // save indexed color for the current LED

                __asm__ __volatile__("twi__slave__on_data_reception_finished__packed4_h3c:");
                copy_color_from_palette(color3_index);
            }
            __asm__ __volatile__("twi__slave__on_data_reception_finished__PACKED4_refresh:");
            leds__refresh__set(1);
        }
        twi__continue(true, false);
        comm_leds__memory__ptr = leds__data;
    } else {
        // Empty message => REFRESH
        // (could also be RESET, but REFRESH seems more useful: fill the video memory and render it to LEDS when necessary)
        leds__refresh__set(1);
        twi__continue(true, false);
    }
}
