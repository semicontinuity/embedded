// LED state data structures tuned for updates of 16 4x4 boards of "abstract" bi-color LEDs.
// BLM Board supports updating a row or a column of LEDS with a 1-byte PACKED4 I2C command.
// For every board, there are 4 rows, and 4 columns.
// So, in total, there are 16 * 4 * 2 * 2 commands possible (x2 commands because of separate commands for each color channel).
// Per board row or column, only the latest command is stored,
// but it should be OK, because I2C commands are sent faster than MIDI commands are received.
// ---------------------------------------------------------------------------------------------------------------------------------

#ifndef __BLM_BOARDS__COMM__LEDS__P4_COMMANDS__BUFFER
#define __BLM_BOARDS__COMM__LEDS__P4_COMMANDS__BUFFER

#include <stdint.h>
#include "debug_midi__arduino_serial.h"
#include "debug_midi__sysex_parameters.h"


uint8_t  blm_boards__comm__leds__p4_commands__buffer__commands[16][16];         // every entry is a 1-byte command to be sent to a board
uint16_t blm_boards__comm__leds__p4_commands__buffer__commands__pending[16];    // 1 bit means that corresponding command for the board is pending
uint16_t blm_boards__comm__leds__p4_commands__buffer__boards_dirty;             // 1 bit means that corresponding board has pending commands


void blm_boards__comm__leds__p4_commands__buffer__init() {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            blm_boards__comm__leds__p4_commands__buffer__commands[i][j] = 0U;
        }
    }
    for (int i = 0; i < 16; i++) {
        blm_boards__comm__leds__p4_commands__buffer__commands__pending[i] = 0U;
    }
    blm_boards__comm__leds__p4_commands__buffer__boards_dirty = 0U;
}


static void blm_boards__comm__leds__p4_commands__buffer__put(uint8_t matrix, uint8_t command_index, uint8_t command) {
    debug_midi__sysex_p8(D_BOARD, matrix);
    blm_boards__comm__leds__p4_commands__buffer__commands[matrix][command_index] = command;
    blm_boards__comm__leds__p4_commands__buffer__commands__pending[matrix] |= (1U << command_index);
    blm_boards__comm__leds__p4_commands__buffer__boards_dirty |= (1U << (uint32_t) matrix);
}


#endif
