#include <stdint.h>
#include "blm_boards_leds.h"
#include "blm_boards_leds__state.h"


void blm_boards_leds__init() {
    for (uint8_t i = 0; i < sizeof(blm_boards_leds__state__current); i++) {
        blm_boards_leds__state__current[i] = 0U;
    }
    for (uint8_t i = 0; i < sizeof(blm_boards_leds__state__requested); i++) {
        blm_boards_leds__state__requested[i] = 0U;
    }
    blm_boards_leds__state__dirty = 0U;
}


void blm_boards_leds__set_one(
        uint8_t matrix_x,
        uint8_t matrix_y,
        uint8_t local_x,
        uint8_t local_y,
        uint8_t r,
        uint8_t g,
        uint8_t b)
{
}
