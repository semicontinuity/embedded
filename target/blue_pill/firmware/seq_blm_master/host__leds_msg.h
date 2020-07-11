// Interface, representing LED update messages from host.
//
// color_code: either 0 or 1; e.g., for RED/GREEN LEDs, 0 is green, 1 is red.
// -----------------------------------------------------------------------------

#include <stdint.h>

void host__leds_msg__select_palette(uint8_t palette);
void host__leds_msg__update_color(uint8_t row, uint8_t column, uint8_t color);
void host__leds_msg__update_one(uint8_t row, uint8_t column, uint8_t color_code);
void host__leds_msg__update_row(uint8_t row, uint8_t is_second_half, uint8_t pattern, uint8_t color_code);
void host__leds_msg__update_column(uint8_t column, uint8_t is_second_half, uint8_t pattern, uint8_t color_code);
void host__leds_msg__update_extra_column(uint8_t is_second_half, uint8_t pattern, uint8_t color_code);
void host__leds_msg__update_extra_row(uint8_t is_second_half, uint8_t pattern, uint8_t color_code);
void host__leds_msg__update_extra(uint8_t is_second_half, uint8_t pattern, uint8_t color_code);
