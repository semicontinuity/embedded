// Implements updating of multi-BLM LEDs PACKED4 commands buffer
// for MidiBox-style commands.
// (Protocol 2)
// -----------------------------------------------------------------------------

#include <Arduino.h>
#include <stdint.h>
#include "blm_boards__comm__leds__p4_commands__buffer.h"
#include "debug__midi_sysex.h"
#include "debug__midi_sysex__parameters.h"


static void host__leds_msg_handler__p4__update_row_or_column(
        uint8_t base_matrix, uint8_t d, uint8_t dir, uint8_t coord, uint8_t pattern, uint8_t color_code)
{
    uint8_t pos = coord & 0x03U;
    uint8_t command_base = (color_code << 7U) + (pos << 5U) + (dir << 4U);
    uint8_t command_index = (pos << 2U) + (color_code << 1U) + (dir << 0U);
    blm_boards__comm__leds__p4_commands__buffer__put(base_matrix + 0, command_index, command_base + (pattern & 0x0FU));
    blm_boards__comm__leds__p4_commands__buffer__put(base_matrix + d, command_index, command_base + ((pattern >> 4U) & 0x0FU));
}

void host__leds_msg_handler__p4__update_row(uint8_t row, uint8_t is_second_half, uint8_t pattern, uint8_t color_code) {
    debug__midi_sysex__p0(D_UPDATE_ROW);
    debug__midi_sysex__p8(D_ROW, row);
    debug__midi_sysex__p8(D_PATTERN, pattern);

    uint8_t matrix_y = row >> 2U;
    uint8_t base_matrix = (matrix_y << 2U) + (is_second_half ? 2 : 0);
    host__leds_msg_handler__p4__update_row_or_column(base_matrix, 1, 0U, row, pattern, color_code);
}

void host__leds_msg_handler__p4__update_column(uint8_t column, uint8_t is_second_half, uint8_t pattern, uint8_t color_code) {
    debug__midi_sysex__p0(D_UPDATE_COLUMN);
    debug__midi_sysex__p8(D_COLUMN, column);
    debug__midi_sysex__p8(D_PATTERN, pattern);

    uint8_t matrix_x = column >> 2U;
    uint8_t base_matrix = matrix_x + (is_second_half ? 8 : 0);
    host__leds_msg_handler__p4__update_row_or_column(base_matrix, 4, 1U, column, pattern, color_code);
}


void host__leds_msg_handler__p4__update_extra_row(uint8_t is_second_half, uint8_t pattern, uint8_t color_code) {
    debug__midi_sysex__p0(D_UPDATE_EX_ROW);
}


void host__leds_msg_handler__p4__update_extra_column(uint8_t is_second_half, uint8_t pattern, uint8_t color_code) {
    debug__midi_sysex__p0(D_UPDATE_EX_COLUMN);
}


void host__leds_msg_handler__p4__update_extra_leds(uint8_t is_second_half, uint8_t pattern, uint8_t color_code) {
    debug__midi_sysex__p0(D_UPDATE_EX);
}
