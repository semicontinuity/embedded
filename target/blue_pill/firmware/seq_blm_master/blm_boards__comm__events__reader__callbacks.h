// Button and encoder events from BLM boards.
// -----------------------------------------------------------------------------
#include <stdint.h>

uint8_t blm_boards__comm_events__button(uint8_t board, uint8_t button, bool is_pressed);

uint8_t blm_boards__comm_events__encoder(uint8_t board, uint8_t encoder, int8_t delta);
