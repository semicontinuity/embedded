// Implements test mode
// -----------------------------------------------------------------------------
#include <stdint.h>
#include "blm_boards__comm__leds__u128_commands__buffer.h"

uint8_t blm_boards__comm_events__handler__test_mode__colors[16][16];

void blm_boards__comm_events__handler__test_mode__init(void) {
    for (uint8_t matrix = 0; matrix < 16; matrix++) {
        for (uint8_t led = 0; led < 16; led++) {
            blm_boards__comm_events__handler__test_mode__colors[matrix][led] = 0;
        }
    }
}

void blm_boards__comm_events__handler__test_mode__on_button_event(uint8_t board, uint8_t button, bool is_pressed) {
    if (!is_pressed)
        return;

    uint8_t color = blm_boards__comm_events__handler__test_mode__colors[board][button];
    ++color;            // cycle thru all 128 colors of palette
    color &= 0x7Fu;     // rollup
    blm_boards__comm_events__handler__test_mode__colors[board][button] = color;
    blm_boards__comm__leds__u128_commands__buffer__put(board, button, color);
}
