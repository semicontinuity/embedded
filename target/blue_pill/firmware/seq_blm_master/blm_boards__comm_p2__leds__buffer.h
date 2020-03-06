// LED state data structures tuned for updates of 16 4x4 boards of "abstract" bi-color LEDs.
// -----------------------------------------------------------------------------

#ifndef __BLM_BOARDS__COMM_P2__LEDS__BUFFER
#define __BLM_BOARDS__COMM_P2__LEDS__BUFFER

#include <stdint.h>

uint8_t  blm_boards__comm_p2__leds__buffer__commands[16 * 4 * 2];
uint32_t blm_boards__comm_p2__leds__buffer__commands__dirty[4 * 2];
uint8_t  blm_boards__comm_p2__leds__buffer__dirty;


void blm_boards__comm_p2__leds__buffer__init() {
    blm_boards__comm_p2__leds__buffer__dirty = 0U;
    for (int i = 0; i < 16*4*2; i++) {
        blm_boards__comm_p2__leds__buffer__commands[i] = 0U;
    }
    for (int i = 0; i < 4*2; i++) {
        blm_boards__comm_p2__leds__buffer__commands__dirty[i] = 0U;
    }
}

#endif
