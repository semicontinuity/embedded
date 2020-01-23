// Scans LED state data structures
// and produces on BLM board LED update commands.
// May generate up to 1 LED update command on every invocation
// of blm_boards_leds__state_scanner__run().
// -----------------------------------------------------------------------------

#include <stdbool.h>
#include "blm_boards_leds__state.h"
#include "blm_boards_leds__state_scanner_callbacks.h"


/** @return true if the board became synchronized (clean), false otherwise */
static bool blm_boards_leds__state_scanner__scan(unsigned int board) {
    uint32_t current = blm_boards_leds__state__current[board];
    uint32_t requested = blm_boards_leds__state__current[board];
    uint32_t raw_diff = current ^ requested;
    uint32_t green_diff = raw_diff & 0xFFFFU;
    uint16_t red_diff = (raw_diff >> 16U) & 0xFFFFU;
    uint16_t diff = green_diff | red_diff;
    int led = __builtin_ffs(diff) - 1;
    if (led >= 0) { // must be always true if there are no bugs
        uint32_t green_mask = 1U << (uint32_t)led;
        uint32_t green = requested & green_mask;
        if (green) {
            current |= green_mask;
            green = 0xFF;
        } else {
            current &= ~green_mask;
        }

        uint32_t red_mask = green_mask << 16U;
        uint32_t red = requested & green_mask;
        if (red) {
            current |= red_mask;
            red = 0xFF;
        } else {
            current &= ~red_mask;
        }

        blm_boards_leds__state__current[board] = current;
        blm_boards_leds__state_scanner__scan__update_one(board, led, red, green, 0);
    }
    return current == requested;
}


void blm_boards_leds__state_scanner__run() {
    int board = __builtin_ffs(blm_boards_leds__state__dirty) - 1;
    if (board >= 0) {
        if (blm_boards_leds__state_scanner__scan(board)) {
            blm_boards_leds__state__dirty &= ~(1U << (uint32_t) board);
        }
    }
    // as optimisation, if all boards are clean, "suspend" the thread, and wake it up when LED updates are received.
    // (on the other hand, this check is quite fast anyway)
}
