#include <stdint.h>

void leds__update_one(uint8_t row, uint8_t column, uint8_t color_code);
void leds__update_row(uint8_t row, uint8_t is_second_half, uint8_t pattern, uint8_t color);
void leds__update_column(uint8_t column, uint8_t is_second_half, uint8_t pattern, uint8_t color);
void leds__update_extra_column(uint8_t is_second_half, uint8_t pattern, uint8_t color);
void leds__update_extra_row(uint8_t is_second_half, uint8_t pattern, uint8_t color);
void leds__update_extra(uint8_t is_second_half, uint8_t pattern, uint8_t color);
