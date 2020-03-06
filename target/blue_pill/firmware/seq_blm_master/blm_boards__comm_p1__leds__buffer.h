// LED state data structures for 16 4x4 boards of "abstract" bi-color LEDs.
// Every element in current and requested state arrays corresponds to one board.
// There are 32 bits per board:
// lower 16 bits are for "green" color, upper for "red".
//
// LEDs and boards are numbered in row-major order.
// If there is difference between some element in "current" and "requested"
// arrays, it means, that corresponding bit is set in the "dirty" bit array,
// and appropriate LED update commands have to be sent
// to the corresponding board.
// -----------------------------------------------------------------------------

#ifndef __BLM_BOARDS__COMM_P1__LEDS__BUFFER
#define __BLM_BOARDS__COMM_P1__LEDS__BUFFER

#include <stdint.h>

uint32_t blm_boards__comm_p1__leds__buffer__current[16];
uint32_t blm_boards__comm_p1__leds__buffer__requested[16];
uint16_t blm_boards__comm_p1__leds__buffer__dirty;


void blm_boards__comm_p1__leds__buffer__init() {
    for (int i = 0; i < 16; i++) {
        blm_boards__comm_p1__leds__buffer__current[i] = 0U;
    }
    for (int i = 0; i < 16; i++) {
        blm_boards__comm_p1__leds__buffer__requested[i] = 0U;
    }
    blm_boards__comm_p1__leds__buffer__dirty = 0U;
}

#endif
