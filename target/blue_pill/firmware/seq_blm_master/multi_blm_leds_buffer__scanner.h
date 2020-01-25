// Scans LED state data structures
// and produces on BLM board LED update commands.
// May generate up to 1 LED update command on every invocation
// of multi_blm_leds_buffer__scanner__run().
// -----------------------------------------------------------------------------

#include <Arduino.h>
#include "multi_blm_leds_buffer.h"
#include "multi_blm_leds_buffer__scanner__callbacks.h"
#include "debug__arduino_serial_midi.h"


/** @return true if the board became synchronized (clean), false otherwise */
static bool multi_blm_leds_buffer__scanner__scan(unsigned int board) {
    debug_p0(D_SCAN);
    debug_p8(D_BOARD, board);

    uint32_t current = multi_blm_leds_buffer__current[board];
    debug_p32(D_CURRENT, current);
    uint32_t requested = multi_blm_leds_buffer__requested[board];
    debug_p32(D_REQUESTED, requested);

    uint32_t raw_diff = current ^ requested;
    debug_p32(D_RAW_DIFF, raw_diff);
    uint16_t green_diff = raw_diff & 0xFFFFU;
    debug_p16(D_GREEN_DIFF, green_diff);
    uint16_t red_diff = (raw_diff >> 16U) & 0xFFFFU;
    debug_p16(D_RED_DIFF, red_diff);
    uint16_t diff = green_diff | red_diff;
    debug_p16(D_DIFF, diff);
    int led = __builtin_ffs(diff) - 1;
    debug_p8(D_LED, led);
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
        uint32_t red = requested & red_mask;
        if (red) {
            current |= red_mask;
            red = 0xFF;
        } else {
            current &= ~red_mask;
        }

        multi_blm_leds_buffer__current[board] = current;
        debug_p32(D_CURRENT, multi_blm_leds_buffer__current[board]);

        multi_blm_leds_buffer__scanner__update_one(board, led, red, green, 0);
    }
    return current == requested;
}


void multi_blm_leds_buffer__scanner__run() {
    int board = __builtin_ffs(multi_blm_leds_buffer__dirty) - 1;
    if (board >= 0) {
        if (multi_blm_leds_buffer__scanner__scan(board)) {
            multi_blm_leds_buffer__dirty &= ~(1U << (uint32_t) board);
        }
    }
    // as optimisation, if all boards are clean, "suspend" the thread, and wake it up when LED updates are received.
    // (on the other hand, this check is quite fast anyway)
}
