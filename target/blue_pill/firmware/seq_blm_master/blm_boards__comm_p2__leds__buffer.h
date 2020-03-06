// LED state data structures tuned for updates of 16 4x4 boards of "abstract" bi-color LEDs.
// For every board, there are 4 rows, that can be updated with I2C command, and 4 columns.
// So, in total, there are 16 * 4 * 2 * 2 commands possible (x2 commands because of separate commands for each color channel)
// If a certain command is to be sent, the corresponding bit is set in blm_boards__comm_p2__leds__buffer__commands.
// ---------------------------------------------------------------------------------------------------------------------------------

#ifndef __BLM_BOARDS__COMM_P2__LEDS__BUFFER
#define __BLM_BOARDS__COMM_P2__LEDS__BUFFER

#include <stdint.h>

uint8_t  blm_boards__comm_p2__leds__buffer__commands[16][16];     // every entry is a 1-byte command to be sent to a board
uint16_t blm_boards__comm_p2__leds__buffer__boards__dirty[16];    // 1 bit means that corresponding board is dirty
uint32_t blm_boards__comm_p2__leds__buffer__dirty;                // 1 bit means that corresponding entry in commands__dirty is dirty (8 bits used)


void blm_boards__comm_p2__leds__buffer__init() {
    blm_boards__comm_p2__leds__buffer__dirty = 0U;
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            blm_boards__comm_p2__leds__buffer__commands[i][j] = 0U;
        }
    }
    for (int i = 0; i < 4*2; i++) {
        blm_boards__comm_p2__leds__buffer__boards__dirty[i] = 0U;
    }
}

#endif
