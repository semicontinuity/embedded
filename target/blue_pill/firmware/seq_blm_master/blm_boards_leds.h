#include <stdint.h>


void blm_boards_leds__init();


void blm_boards_leds__update_one(
        uint8_t matrix_x,
        uint8_t matrix_y,
        uint8_t local_x,
        uint8_t local_y,
        uint8_t r,
        uint8_t g,
        uint8_t b);
