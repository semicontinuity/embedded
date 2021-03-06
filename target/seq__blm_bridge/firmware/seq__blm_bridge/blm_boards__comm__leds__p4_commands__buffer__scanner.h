// Scans buffer with pending PACKED4 commands
// and produces PACKED4 LED update commands for BLM boards.
// May generate up to 1 LED update command on every invocation
// of blm_boards__comm__leds__p4_commands__buffer__scanner__run().
// (Protocol 2)
// -----------------------------------------------------------------------------

#include <Arduino.h>
#include "blm_boards__comm__leds__p4_commands__buffer.h"
#include "blm_boards__comm__leds__p4_commands__buffer__scanner__callbacks.h"
#include "debug__midi_sysex.h"


static uint16_t blm_boards__comm__leds__p4_commands__buffer__scanner__mask = 0xFFFFU;

/**
 * Finds pending command for the given board and passes it to the appropriate callback.
 * @return true if the board became synchronized (clean), false otherwise
 */
static bool blm_boards__comm__leds__p4_commands__buffer__scanner__scan(unsigned int board) {
    uint16_t dirty_commands = blm_boards__comm__leds__p4_commands__buffer__commands__pending[board];
    int index = __builtin_ffs(dirty_commands) - 1;
    if (index >= 0) {
        blm_boards__comm__leds__p4_commands__buffer__scanner__emit_command(
                board, blm_boards__comm__leds__p4_commands__buffer__commands[board][index]
        );
        dirty_commands &= ~(1U << (uint16_t) index);
        blm_boards__comm__leds__p4_commands__buffer__commands__pending[board] = dirty_commands;
        return dirty_commands == 0U;
    }
    return false;
}


bool blm_boards__comm__leds__p4_commands__buffer__scanner__is_runnable() {
    return blm_boards__comm__leds__p4_commands__buffer__boards_dirty;
}

void blm_boards__comm__leds__p4_commands__buffer__scanner__run() {
    int board = __builtin_ffs(blm_boards__comm__leds__p4_commands__buffer__boards_dirty) - 1;
    if (board >= 0) {
        if (blm_boards__comm__leds__p4_commands__buffer__scanner__scan(board)) {
            blm_boards__comm__leds__p4_commands__buffer__boards_dirty &= ~(1U << (uint32_t) board);
        }
        // mask out current board index and all lower indices
        // the boar may remain dirty, and it will be processed in the next run (fairness)
        blm_boards__comm__leds__p4_commands__buffer__scanner__mask = (0xFFFFU << (board + 1U));
    }
    if (blm_boards__comm__leds__p4_commands__buffer__scanner__mask == 0U) {
        // run finished, scanned all bits, roll over
        blm_boards__comm__leds__p4_commands__buffer__scanner__mask = 0xFFFFU;
    }
    // as optimisation, if all boards are clean, "suspend" the thread, and wake it up when LED updates are received.
    // (on the other hand, this check is quite fast anyway)
}
