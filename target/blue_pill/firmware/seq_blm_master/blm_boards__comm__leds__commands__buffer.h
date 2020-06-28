// LED state data structures tuned for updates of 16 4x4 boards of "abstract" bi-color LEDs.
// BLM Board supports uprating a row or a column of LEDS with a 1-byte PACKED4 I2C command.
// For every board, there are 4 rows, and 4 columns.
// So, in total, there are 16 * 4 * 2 * 2 commands possible (x2 commands because of separate commands for each color channel)
// If a certain command is to be sent, the corresponding bit is set in blm_boards__comm__leds__commands__buffer__commands.
// ---------------------------------------------------------------------------------------------------------------------------------

#ifndef __BLM_BOARDS__COMM__LEDS__COMMANDS__BUFFER
#define __BLM_BOARDS__COMM__LEDS__COMMANDS__BUFFER

#include <stdint.h>
#include "debug_midi__arduino_serial.h"
#include "debug_midi__sysex_parameters.h"


uint8_t  blm_boards__comm__leds__commands__buffer__commands[16][16];     // every entry is a 1-byte command to be sent to a board
uint16_t blm_boards__comm__leds__commands__buffer__commands__dirty[16];  // 1 bit means that corresponding command for the board is dirty
uint16_t blm_boards__comm__leds__commands__buffer__dirty;                // 1 bit means that corresponding entry in commands__dirty is dirty


void blm_boards__comm__leds__commands__buffer__init() {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            blm_boards__comm__leds__commands__buffer__commands[i][j] = 0U;
        }
    }
    for (int i = 0; i < 16; i++) {
        blm_boards__comm__leds__commands__buffer__commands__dirty[i] = 0U;
    }
    blm_boards__comm__leds__commands__buffer__dirty = 0U;
}


static void blm_boards__comm__leds__commands__buffer__put(uint8_t matrix, uint8_t command_index, uint8_t command) {
    debug_midi__sysex_p8(D_BOARD, matrix);
    blm_boards__comm__leds__commands__buffer__commands[matrix][command_index] = command;
    blm_boards__comm__leds__commands__buffer__commands__dirty[matrix] |= (1U << command_index);
}


#endif
