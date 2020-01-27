// Button and encoder events from BLM boards.
// -----------------------------------------------------------------------------
#include <stdint.h>

void blm_boards__comm_events__handler__on_button_event(uint8_t board, uint8_t button, bool is_pressed);
