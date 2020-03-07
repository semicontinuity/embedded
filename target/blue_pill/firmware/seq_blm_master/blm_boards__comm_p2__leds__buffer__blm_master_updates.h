// Implements updating of multi-BLM LEDs data buffer
// for blm_master-style commands.
// (Protocol 2)
// -----------------------------------------------------------------------------

#include <Arduino.h>
#include <stdint.h>
#include "blm_master__leds.h"
#include "blm_boards__comm_p2__leds__buffer.h"
#include "debug_midi__arduino_serial.h"
#include "debug_midi__sysex_parameters.h"


// Implements blm_master__leds.h
// -----------------------------------------------------------------------------

void blm_boards__comm_p2__leds__buffer__blm_master__update_one(uint8_t row, uint8_t column, uint8_t color_code) {
    debug_midi__sysex_p0(D_UPDATE_ONE);
    uint8_t matrix_x = ((uint8_t)(column >> 2U)) & 0x03U;
    uint8_t matrix_y = row >> 2U;
    uint8_t matrix = (matrix_y << 2U) + matrix_x;
    debug_midi__sysex_p8(D_BOARD, matrix);

    uint8_t local_x = column & 0x03U;
    uint8_t local_y = row & 0x03U;
    uint8_t led = (local_y << 2U) + local_x;
    debug_midi__sysex_p8(D_LED, led);
}


void blm_boards__comm_p2__leds__buffer__blm_master__update_row(uint8_t row, uint8_t is_second_half, uint8_t pattern, uint8_t color_code) {
    debug_midi__sysex_p0(D_UPDATE_ROW);
    debug_midi__sysex_p8(D_ROW, row);
    debug_midi__sysex_p8(D_PATTERN, pattern);

    uint8_t matrix_y = row >> 2U;
    uint8_t base_matrix = (matrix_y << 2U) + (is_second_half ? 2 : 0);
    blm_boards__comm_p2__leds__buffer__blm_master__put_commands(base_matrix, 1, 0U, row, pattern, color_code);
}

void blm_boards__comm_p2__leds__buffer__blm_master__update_column(uint8_t column, uint8_t is_second_half, uint8_t pattern, uint8_t color_code) {
    debug_midi__sysex_p0(D_UPDATE_COLUMN);
    debug_midi__sysex_p8(D_COLUMN, column);
    debug_midi__sysex_p8(D_PATTERN, pattern);

    uint8_t matrix_x = column >> 2U;
    uint8_t base_matrix = matrix_x + (is_second_half ? 8 : 0);
    blm_boards__comm_p2__leds__buffer__blm_master__put_commands(base_matrix, 4, 1U, column, pattern, color_code);
}


void blm_boards__comm_p2__leds__buffer__blm_master__update_extra_row(uint8_t is_second_half, uint8_t pattern, uint8_t color_code) {
    debug_midi__sysex_p0(D_UPDATE_EX_ROW);
}


void blm_boards__comm_p2__leds__buffer__blm_master__update_extra_column(uint8_t is_second_half, uint8_t pattern, uint8_t color_code) {
    debug_midi__sysex_p0(D_UPDATE_EX_COLUMN);
}


void blm_boards__comm_p2__leds__buffer__blm_master__update_extra(uint8_t is_second_half, uint8_t pattern, uint8_t color_code) {
    debug_midi__sysex_p0(D_UPDATE_EX);
}
