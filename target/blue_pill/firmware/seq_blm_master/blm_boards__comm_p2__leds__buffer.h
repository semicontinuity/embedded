// LED state data structures tuned for updates of 16 4x4 boards of "abstract" bi-color LEDs.
// For every board, there are 4 rows, that can be updated with I2C command, and 4 columns.
// So, in total, there are 16 * 4 * 2 * 2 commands possible (x2 commands because of separate commands for each color channel)
// If a certain command is to be sent, the corresponding bit is set in blm_boards__comm_p2__leds__buffer__commands.
// ---------------------------------------------------------------------------------------------------------------------------------

#ifndef __BLM_BOARDS__COMM_P2__LEDS__BUFFER
#define __BLM_BOARDS__COMM_P2__LEDS__BUFFER

#include <stdint.h>
#include "debug_midi__arduino_serial.h"
#include "debug_midi__sysex_parameters.h"


uint8_t  blm_boards__comm_p2__leds__buffer__commands[16][16];     // every entry is a 1-byte command to be sent to a board
uint16_t blm_boards__comm_p2__leds__buffer__commands__dirty[16];  // 1 bit means that corresponding command for the board is dirty
uint32_t blm_boards__comm_p2__leds__buffer__dirty;                // 1 bit means that corresponding entry in commands__dirty is dirty (8 bits used)


void blm_boards__comm_p2__leds__buffer__init() {
    blm_boards__comm_p2__leds__buffer__dirty = 0U;
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            blm_boards__comm_p2__leds__buffer__commands[i][j] = 0U;
        }
    }
    for (int i = 0; i < 4*2; i++) {
        blm_boards__comm_p2__leds__buffer__commands__dirty[i] = 0U;
    }
}


static void blm_boards__comm_p2__leds__buffer__blm_master__put_command(uint8_t matrix, uint8_t command_index, uint8_t command) {
    debug_midi__sysex_p8(D_BOARD, matrix);
    blm_boards__comm_p2__leds__buffer__commands[matrix][command_index] = command;
    blm_boards__comm_p2__leds__buffer__commands__dirty[matrix] |= (1U << command_index);
}


void blm_boards__comm_p2__leds__buffer__blm_master__put_commands(
    uint8_t base_matrix, uint8_t d, uint8_t dir, uint8_t coord, uint8_t pattern, uint8_t color_code)
{
    uint8_t pos = coord & 0x03U;
    uint8_t command_base = (color_code << 7U) + (pos << 5U) + (dir << 4U);
    uint8_t command_index = (pos << 2U) + (color_code << 1U) + (dir << 0U);
    blm_boards__comm_p2__leds__buffer__blm_master__put_command(base_matrix + 0, command_index, command_base + (pattern & 0x0FU));
    blm_boards__comm_p2__leds__buffer__blm_master__put_command(base_matrix + d, command_index, command_base + ((pattern >> 4U) & 0x0FU));
}


#endif
