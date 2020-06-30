// Interface, representing BLM_MASTER LED update messages
//
// color_code: either 0 or 1; e.g., for RED/GREEN LEDs, 0 is green, 1 is red.
// -----------------------------------------------------------------------------

#include <stdint.h>

void blm_master__leds__select_palette(uint8_t palette);
void blm_master__leds__update_color(uint8_t row, uint8_t column, uint8_t color);
void blm_master__leds__update_one(uint8_t row, uint8_t column, uint8_t color_code);
void blm_master__leds__update_row(uint8_t row, uint8_t is_second_half, uint8_t pattern, uint8_t color_code);
void blm_master__leds__update_column(uint8_t column, uint8_t is_second_half, uint8_t pattern, uint8_t color_code);
void blm_master__leds__update_extra_column(uint8_t is_second_half, uint8_t pattern, uint8_t color_code);
void blm_master__leds__update_extra_row(uint8_t is_second_half, uint8_t pattern, uint8_t color_code);
void blm_master__leds__update_extra(uint8_t is_second_half, uint8_t pattern, uint8_t color_code);
