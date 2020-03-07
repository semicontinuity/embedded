// Implements updating of multi-BLM LEDs data buffer
// for blm_master-style commands.
// (Protocol 1)
// -----------------------------------------------------------------------------

#include <Arduino.h>
#include <stdint.h>
#include "blm_master__leds.h"
#include "blm_boards__comm_p1__leds__buffer.h"
#include "debug_midi__arduino_serial.h"
#include "debug_midi__sysex_parameters.h"




void blm_boards__comm_p1__leds__buffer__blm_master__update_one(uint8_t row, uint8_t column, uint8_t color_code) {
    debug_midi__sysex_p0(D_UPDATE_ONE);
    uint8_t matrix_x = ((uint8_t)(column >> 2U)) & 0x03U;
    uint8_t matrix_y = row >> 2U;
    uint8_t matrix = (matrix_y << 2U) + matrix_x;
    debug_midi__sysex_p8(D_BOARD, matrix);

    uint8_t local_x = column & 0x03U;
    uint8_t local_y = row & 0x03U;
    uint8_t led = (local_y << 2U) + local_x;
    debug_midi__sysex_p8(D_LED, led);

    uint8_t green = (color_code & 0x20U) ? 0xFF : 0x00;
    uint8_t red = (color_code & 0x40U) ? 0xFF : 0x00;

    uint32_t requested = blm_boards__comm_p1__leds__buffer__requested[matrix];
    if (green) { requested |= (1U << led); } else { requested &= ~(1U << led); }
    if (red) { requested |= (1U << (led + 16U)); } else { requested &= ~(1U << (led + 16U)); }
    debug_midi__sysex_p32(D_REQUESTED, requested);
    blm_boards__comm_p1__leds__buffer__requested[matrix] = requested;

    uint32_t current = blm_boards__comm_p1__leds__buffer__current[matrix];
    debug_midi__sysex_p32(D_CURRENT, current);
    if (current != requested) {
        blm_boards__comm_p1__leds__buffer__dirty |= (1U << matrix);
        debug_midi__sysex_p16(D_DIRTY, blm_boards__comm_p1__leds__buffer__dirty);
    }
}


void blm_boards__comm_p1__leds__buffer__blm_master__update_row(uint8_t row, uint8_t is_second_half, uint8_t pattern, uint8_t color_code) {
    debug_midi__sysex_p0(D_UPDATE_ROW);
    debug_midi__sysex_p8(D_ROW, row);
    debug_midi__sysex_p8(D_PATTERN, pattern);
    
    uint8_t matrix_y = row >> 2U;
    uint8_t matrix = (matrix_y << 2U) + (is_second_half ? 2 : 0);

    uint8_t local_y = row & 0x03U;
    uint8_t shift = (color_code ? 16 : 0) + (local_y << 2U);
    debug_midi__sysex_p8(D_SHIFT, shift);
    uint32_t mask = ~(0x000FU << shift);
    debug_midi__sysex_p32(D_MASK, mask);

    blm_boards__comm_p1__leds__buffer__update_h_nibble(matrix + 0, shift, mask, pattern & 0x0FU);
    blm_boards__comm_p1__leds__buffer__update_h_nibble(matrix + 1, shift, mask, (pattern >> 4U) & 0x0FU);
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


void blm_boards__comm_p1__leds__buffer__blm_master__update_column(uint8_t column, uint8_t is_second_half, uint8_t pattern, uint8_t color_code) {
    debug_midi__sysex_p0(D_UPDATE_COLUMN);
    debug_midi__sysex_p8(D_COLUMN, column);
    debug_midi__sysex_p8(D_PATTERN, pattern);

    uint8_t matrix_y = column >> 2U;
    uint8_t matrix = matrix_y + (is_second_half ? 8 : 0);
    uint8_t local_x = column & 0x03U;

    uint8_t initial_shift = (color_code ? 16 : 0) + local_x;
    debug_midi__sysex_p8(D_SHIFT, initial_shift);

    blm_boards__comm_p1__leds__buffer__update_v_nibble(matrix + 0, initial_shift, pattern);
    blm_boards__comm_p1__leds__buffer__update_v_nibble(matrix + 4, initial_shift, pattern);
}


void blm_boards__comm_p1__leds__buffer__blm_master__update_extra_row(uint8_t is_second_half, uint8_t pattern, uint8_t color_code) {
    debug_midi__sysex_p0(D_UPDATE_EX_ROW);
}


void blm_boards__comm_p1__leds__buffer__blm_master__update_extra_column(uint8_t is_second_half, uint8_t pattern, uint8_t color_code) {
    debug_midi__sysex_p0(D_UPDATE_EX_COLUMN);
}


void blm_boards__comm_p1__leds__buffer__blm_master__update_extra(uint8_t is_second_half, uint8_t pattern, uint8_t color_code) {
    debug_midi__sysex_p0(D_UPDATE_EX);
}
