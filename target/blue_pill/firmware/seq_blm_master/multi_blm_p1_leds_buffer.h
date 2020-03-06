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

#ifndef __BLM_BOARDS_LEDS__STATE
#define __BLM_BOARDS_LEDS__STATE

#include <stdint.h>

uint32_t multi_blm_p1_leds_buffer__current[16];
uint32_t multi_blm_p1_leds_buffer__requested[16];
uint16_t multi_blm_p1_leds_buffer__dirty;

void multi_blm_p1_leds_buffer__init() {
    for (int i = 0; i < 16; i++) {
        multi_blm_p1_leds_buffer__current[i] = 0U;
    }
    for (int i = 0; i < 16; i++) {
        multi_blm_p1_leds_buffer__requested[i] = 0U;
    }
    multi_blm_p1_leds_buffer__dirty = 0U;
}

#endif
