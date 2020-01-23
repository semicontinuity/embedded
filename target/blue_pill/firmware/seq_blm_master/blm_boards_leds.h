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


void blm_boards_leds__update_row(uint8_t row, uint8_t is_second_half, uint8_t pattern, uint8_t color);
void blm_boards_leds__update_column(uint8_t column, uint8_t is_second_half, uint8_t pattern, uint8_t color);
void blm_boards_leds__update_extra_column(uint8_t is_second_half, uint8_t pattern, uint8_t color);
void blm_boards_leds__update_extra_row(uint8_t is_second_half, uint8_t pattern, uint8_t color);
void update_extra_leds(uint8_t is_second_half, uint8_t pattern, uint8_t color);
