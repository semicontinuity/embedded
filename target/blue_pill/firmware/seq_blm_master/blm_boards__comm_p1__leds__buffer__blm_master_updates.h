// Implements updating of multi-BLM LEDs data buffer
// for blm_master-style commands.
// (Protocol 1)
// -----------------------------------------------------------------------------

#include <Arduino.h>
#include <stdint.h>
#include "blm_master__leds.h"
#include "blm_boards__comm_p1__leds__buffer.h"
#include "debug__arduino_serial_midi.h"


void blm_boards__comm_p1__leds__buffer__blm_master__update_one(uint8_t row, uint8_t column, uint8_t color_code) {
    debug_p0(D_UPDATE_ONE);
    uint8_t local_x = column & 0x03U;
    uint8_t local_y = row & 0x03U;

    uint8_t green = (color_code & 0x20U) ? 0xFF : 0x00;
    uint8_t red = (color_code & 0x40U) ? 0xFF : 0x00;

    uint8_t matrix_x = ((uint8_t)(column >> 2U)) & 0x03U;
    uint8_t matrix_y = row >> 2U;

    uint8_t matrix = (matrix_y << 2U) + matrix_x;
    debug_p8(D_BOARD, matrix);
    uint8_t led = (local_y << 2U) + local_x;
    debug_p8(D_LED, led);
    uint32_t requested = blm_boards__comm_p1__leds__buffer__requested[matrix];
    if (green) { requested |= (1U << led); } else { requested &= ~(1U << led); }
    if (red) { requested |= (1U << (led + 16U)); } else { requested &= ~(1U << (led + 16U)); }
    debug_p32(D_REQUESTED, requested);
    blm_boards__comm_p1__leds__buffer__requested[matrix] = requested;

    uint32_t current = blm_boards__comm_p1__leds__buffer__current[matrix];
    debug_p32(D_CURRENT, current);
    if (current != requested) {
        blm_boards__comm_p1__leds__buffer__dirty |= (1U << matrix);
        debug_p16(D_DIRTY, blm_boards__comm_p1__leds__buffer__dirty);
    }
}


void blm_boards__comm_p1__leds__buffer__blm_master__update_row(uint8_t row, uint8_t is_second_half, uint8_t pattern, uint8_t color_code) {
    debug_p0(D_UPDATE_ROW);
    debug_p8(D_ROW, row);
    debug_p8(D_PATTERN, pattern);
    uint8_t matrix = ((row >> 2U) << 2U) + (is_second_half ? 2 : 0);
    debug_p8(D_BOARD, matrix);
    uint8_t shift = (color_code ? 16 : 0) + ((row & 0x03U) << 2U);
    debug_p8(D_SHIFT, shift);
    uint32_t mask = ~(0x000FU << shift);
    debug_p32(D_MASK, mask);

    uint32_t requested;
    uint32_t current;

    requested = blm_boards__comm_p1__leds__buffer__requested[matrix];
    debug_p32(D_REQUESTED, requested);
    requested = (requested & mask) | ((pattern & 0x0FU) << shift);
    debug_p32(D_REQUESTED, requested);
    blm_boards__comm_p1__leds__buffer__requested[matrix] = requested;

    current = blm_boards__comm_p1__leds__buffer__current[matrix];
    debug_p32(D_CURRENT, current);
    if (requested != current) {
        blm_boards__comm_p1__leds__buffer__dirty |= (1U << matrix);
        debug_p16(D_DIRTY, blm_boards__comm_p1__leds__buffer__dirty);
    }

    ++matrix;
    debug_p8(D_BOARD, matrix);

    requested = blm_boards__comm_p1__leds__buffer__requested[matrix];
    debug_p32(D_REQUESTED, requested);
    requested = (requested & mask) | (((pattern >> 4U) & 0x0FU) << shift);
    debug_p32(D_REQUESTED, requested);
    blm_boards__comm_p1__leds__buffer__requested[matrix] = requested;

    current = blm_boards__comm_p1__leds__buffer__current[matrix];
    debug_p32(D_CURRENT, current);
    if (requested != current) {
        blm_boards__comm_p1__leds__buffer__dirty |= (1U << matrix);
        debug_p16(D_DIRTY, blm_boards__comm_p1__leds__buffer__dirty);
    }
}


void blm_boards__comm_p1__leds__buffer__blm_master__update_column(uint8_t column, uint8_t is_second_half, uint8_t pattern, uint8_t color_code) {
    debug_p0(D_UPDATE_COLUMN);
    debug_p8(D_COLUMN, column);
    debug_p8(D_PATTERN, pattern);
    uint8_t matrix = (column >> 2U) + (is_second_half ? 8 : 0);
    debug_p8(D_BOARD, matrix);
    uint8_t initial_shift = (color_code ? 16 : 0) + (column & 0x03U);
    debug_p8(D_SHIFT, initial_shift);

    uint32_t requested;
    uint32_t current;
    uint32_t set_mask;
    uint32_t shift;

    requested = blm_boards__comm_p1__leds__buffer__requested[matrix];
    debug_p32(D_REQUESTED, requested);
    shift = initial_shift;

    // bit 0 of pattern
    debug_p8(D_SHIFT, shift);
    debug_p8(D_PATTERN, pattern);
    set_mask = (pattern & 0x01U) << shift;
    debug_p32(D_MASK, set_mask);
    requested = (requested & ~(0x0001U << shift)) | set_mask;
    debug_p32(D_REQUESTED, requested);

    pattern >>= 1U;
    shift += 4;

    // bit 1 of pattern
    debug_p8(D_SHIFT, shift);
    debug_p8(D_PATTERN, pattern);
    set_mask = (pattern & 0x01U) << shift;
    debug_p32(D_MASK, set_mask);
    requested = (requested & ~(0x0001U << shift)) | set_mask;
    debug_p32(D_REQUESTED, requested);

    pattern >>= 1U;
    shift += 4;

    // bit 2 of pattern
    debug_p8(D_SHIFT, shift);
    debug_p8(D_PATTERN, pattern);
    set_mask = (pattern & 0x01U) << shift;
    debug_p32(D_MASK, set_mask);
    requested = (requested & ~(0x0001U << shift)) | set_mask;
    debug_p32(D_REQUESTED, requested);

    pattern >>= 1U;
    shift += 4;

    // bit 3 of pattern
    debug_p8(D_SHIFT, shift);
    debug_p8(D_PATTERN, pattern);
    set_mask = (pattern & 0x01U) << shift;
    debug_p32(D_MASK, set_mask);
    requested = (requested & ~(0x0001U << shift)) | set_mask;
    debug_p32(D_REQUESTED, requested);

    pattern >>= 1U;
    shift = initial_shift;

    blm_boards__comm_p1__leds__buffer__requested[matrix] = requested;
    current = blm_boards__comm_p1__leds__buffer__current[matrix];
    debug_p32(D_CURRENT, current);
    if (current != requested) {
        blm_boards__comm_p1__leds__buffer__dirty |= (1U << matrix);
        debug_p16(D_DIRTY, blm_boards__comm_p1__leds__buffer__dirty);
    }

    matrix += 4;
    debug_p8(D_BOARD, matrix);

    requested = blm_boards__comm_p1__leds__buffer__requested[matrix];
    debug_p32(D_REQUESTED, requested);

    // bit 4 of pattern
    debug_p8(D_SHIFT, shift);
    debug_p8(D_PATTERN, pattern);
    set_mask = (pattern & 0x01U) << shift;
    debug_p32(D_MASK, set_mask);
    requested = (requested & ~(0x0001U << shift)) | set_mask;
    debug_p32(D_REQUESTED, requested);

    pattern >>= 1U;
    shift += 4;

    // bit 5 of pattern
    debug_p8(D_SHIFT, shift);
    debug_p8(D_PATTERN, pattern);
    set_mask = (pattern & 0x01U) << shift;
    debug_p32(D_MASK, set_mask);
    requested = (requested & ~(0x0001U << shift)) | set_mask;
    debug_p32(D_REQUESTED, requested);

    pattern >>= 1U;
    shift += 4;

    // bit 6 of pattern
    debug_p8(D_SHIFT, shift);
    debug_p8(D_PATTERN, pattern);
    set_mask = (pattern & 0x01U) << shift;
    debug_p32(D_MASK, set_mask);
    requested = (requested & ~(0x0001U << shift)) | set_mask;
    debug_p32(D_REQUESTED, requested);

    pattern >>= 1U;
    shift += 4;

    // bit 7 of pattern
    debug_p8(D_SHIFT, shift);
    debug_p8(D_PATTERN, pattern);
    set_mask = (pattern & 0x01U) << shift;
    debug_p32(D_MASK, set_mask);
    requested = (requested & ~(0x0001U << shift)) | set_mask;
    debug_p32(D_REQUESTED, requested);

    blm_boards__comm_p1__leds__buffer__requested[matrix] = requested;
    current = blm_boards__comm_p1__leds__buffer__current[matrix];
    debug_p32(D_CURRENT, current);
    if (current != requested) {
        blm_boards__comm_p1__leds__buffer__dirty |= (1U << matrix);
        debug_p16(D_DIRTY, blm_boards__comm_p1__leds__buffer__dirty);
    }
}


void blm_boards__comm_p1__leds__buffer__blm_master__update_extra_row(uint8_t is_second_half, uint8_t pattern, uint8_t color_code) {
    debug_p0(D_UPDATE_EX_ROW);
}


void blm_boards__comm_p1__leds__buffer__blm_master__update_extra_column(uint8_t is_second_half, uint8_t pattern, uint8_t color_code) {
    debug_p0(D_UPDATE_EX_COLUMN);
}


void blm_boards__comm_p1__leds__buffer__blm_master__update_extra(uint8_t is_second_half, uint8_t pattern, uint8_t color_code) {
    debug_p0(D_UPDATE_EX);
}
