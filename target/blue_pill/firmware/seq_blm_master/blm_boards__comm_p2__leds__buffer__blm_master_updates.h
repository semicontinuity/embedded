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
    uint8_t pos = row & 0x03U;
    uint8_t command_base = (color_code << 7U) + (pos << 5U) + (0U << 4U);
    uint8_t command_index = 1U << ((pos << 2U) + (color_code << 1U) + (0U << 0U));

    uint8_t matrix = (matrix_y << 2U) + (is_second_half ? 2 : 0);
    debug_midi__sysex_p8(D_BOARD, matrix);
    uint8_t command1 = command_base + (pattern & 0x0FU);

    blm_boards__comm_p2__leds__buffer__commands[matrix][command_index] = command1;
    blm_boards__comm_p2__leds__buffer__commands__dirty[matrix] |= (1U << command_index);

    ++matrix;
    debug_midi__sysex_p8(D_BOARD, matrix);
    uint8_t command2 = command_base + ((pattern >> 4U) & 0x0FU);
    blm_boards__comm_p2__leds__buffer__commands[matrix][command_index] = command2;
    blm_boards__comm_p2__leds__buffer__commands__dirty[matrix] = command_index;
}


void blm_boards__comm_p2__leds__buffer__blm_master__update_column(uint8_t column, uint8_t is_second_half, uint8_t pattern, uint8_t color_code) {
    debug_midi__sysex_p0(D_UPDATE_COLUMN);
    debug_midi__sysex_p8(D_COLUMN, column);
    debug_midi__sysex_p8(D_PATTERN, pattern);

    uint8_t matrix_x = column >> 2U;
    uint8_t pos = column & 0x03U;
    uint8_t command_base = (color_code << 7U) + (pos << 5U) + (1U << 4U);
    uint8_t command_index = 1U << ((pos << 2U) + (color_code << 1U) + (0U << 0U));
    
    uint8_t matrix = matrix_x + (is_second_half ? 8 : 0);
    debug_midi__sysex_p8(D_BOARD, matrix);
    uint8_t command1 = command_base + (pattern & 0x0FU);
    blm_boards__comm_p2__leds__buffer__commands[matrix][command_index] = command1;
    blm_boards__comm_p2__leds__buffer__commands__dirty[matrix] |= (1U << command_index);
    
    matrix += 4;
    debug_midi__sysex_p8(D_BOARD, matrix);
    uint8_t command2 = command_base + ((pattern >> 4U) & 0x0FU);
    blm_boards__comm_p2__leds__buffer__commands[matrix][command_index] = command2;
    blm_boards__comm_p2__leds__buffer__commands__dirty[matrix] |= (1U << command_index);
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
