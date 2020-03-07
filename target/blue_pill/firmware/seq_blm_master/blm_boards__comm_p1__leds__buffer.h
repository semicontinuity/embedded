// LED state data structures for 16 4x4 boards of "abstract" bi-color LEDs.
// Every element in current and requested state arrays corresponds to one board.
// There are 32 bits per board:
// lower 16 bits are for "green" color, upper for "red".
//
// LEDs and boards are numbered in row-major order.
// If there is difference between some element in "current" and "requested"
// arrays, it means, that corresponding bit is set in the "dirty" bit array,
// and appropriate LED update commands have to be sent
// to the corresponding board.
// -----------------------------------------------------------------------------

#ifndef __BLM_BOARDS__COMM_P1__LEDS__BUFFER
#define __BLM_BOARDS__COMM_P1__LEDS__BUFFER

#include <stdint.h>
#include "debug_midi__arduino_serial.h"
#include "debug_midi__sysex_parameters.h"

uint32_t blm_boards__comm_p1__leds__buffer__current[16];
uint32_t blm_boards__comm_p1__leds__buffer__requested[16];
uint16_t blm_boards__comm_p1__leds__buffer__dirty;


void blm_boards__comm_p1__leds__buffer__init() {
    for (int i = 0; i < 16; i++) {
        blm_boards__comm_p1__leds__buffer__current[i] = 0U;
    }
    for (int i = 0; i < 16; i++) {
        blm_boards__comm_p1__leds__buffer__requested[i] = 0U;
    }
    blm_boards__comm_p1__leds__buffer__dirty = 0U;
}


/**
 * @return true if buffer data was updated and marked dirty
 */
uint8_t blm_boards__comm_p1__leds__buffer__update_h_nibble(uint8_t matrix, uint8_t shift, uint32_t mask, uint8_t bits) {
    uint32_t requested = blm_boards__comm_p1__leds__buffer__requested[matrix];
    debug_midi__sysex_p32(D_REQUESTED, requested);
    uint32_t new_requested = (requested & mask) | (bits << shift);
    if (requested == new_requested) {
        return false;
    }
    requested = new_requested;
    debug_midi__sysex_p32(D_REQUESTED, requested);
    blm_boards__comm_p1__leds__buffer__requested[matrix] = requested;

    uint32_t current = blm_boards__comm_p1__leds__buffer__current[matrix];
    debug_midi__sysex_p32(D_CURRENT, current);
    if (requested == current) {
        return false;
    }
    blm_boards__comm_p1__leds__buffer__dirty |= (1U << matrix);
    debug_midi__sysex_p16(D_DIRTY, blm_boards__comm_p1__leds__buffer__dirty);
    return true;
}


void blm_boards__comm_p1__leds__buffer__update_v_nibble(uint8_t matrix, uint32_t shift, uint8_t pattern) {
    debug_midi__sysex_p8(D_BOARD, matrix);

    uint32_t requested = blm_boards__comm_p1__leds__buffer__requested[matrix];
    debug_midi__sysex_p32(D_REQUESTED, requested);

    uint32_t set_mask;

    // bit 0/4 of pattern
    debug_midi__sysex_p8(D_SHIFT, shift);
    debug_midi__sysex_p8(D_PATTERN, pattern);
    set_mask = (pattern & 0x01U) << shift;
    debug_midi__sysex_p32(D_MASK, set_mask);
    requested = (requested & ~(0x0001U << shift)) | set_mask;
    debug_midi__sysex_p32(D_REQUESTED, requested);

    pattern >>= 1U;
    shift += 4;

    // bit 1/5 of pattern
    debug_midi__sysex_p8(D_SHIFT, shift);
    debug_midi__sysex_p8(D_PATTERN, pattern);
    set_mask = (pattern & 0x01U) << shift;
    debug_midi__sysex_p32(D_MASK, set_mask);
    requested = (requested & ~(0x0001U << shift)) | set_mask;
    debug_midi__sysex_p32(D_REQUESTED, requested);

    pattern >>= 1U;
    shift += 4;

    // bit 2/6 of pattern
    debug_midi__sysex_p8(D_SHIFT, shift);
    debug_midi__sysex_p8(D_PATTERN, pattern);
    set_mask = (pattern & 0x01U) << shift;
    debug_midi__sysex_p32(D_MASK, set_mask);
    requested = (requested & ~(0x0001U << shift)) | set_mask;
    debug_midi__sysex_p32(D_REQUESTED, requested);

    pattern >>= 1U;
    shift += 4;

    // bit 3/7 of pattern
    debug_midi__sysex_p8(D_SHIFT, shift);
    debug_midi__sysex_p8(D_PATTERN, pattern);
    set_mask = (pattern & 0x01U) << shift;
    debug_midi__sysex_p32(D_MASK, set_mask);
    requested = (requested & ~(0x0001U << shift)) | set_mask;
    debug_midi__sysex_p32(D_REQUESTED, requested);

    blm_boards__comm_p1__leds__buffer__requested[matrix] = requested;
    uint32_t current = blm_boards__comm_p1__leds__buffer__current[matrix];
    debug_midi__sysex_p32(D_CURRENT, current);
    if (current != requested) {
        blm_boards__comm_p1__leds__buffer__dirty |= (1U << matrix);
        debug_midi__sysex_p16(D_DIRTY, blm_boards__comm_p1__leds__buffer__dirty);
    }
}

#endif
