// Interface to read events from BLM boards
// -----------------------------------------------------------------------------

#include <Arduino.h>
#include <stdint.h>

void blm_boards__comm__init();
uint8_t blm_boards__comm__events__read();
void blm_boards__comm__leds__update_one(uint8_t board, uint8_t led, uint8_t r, uint8_t g, uint8_t b);

