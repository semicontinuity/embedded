// Scans LED state data structures
// and produces on BLM board LED update commands.
// May generate up to 1 LED update command on every invocation
// of blm_boards__comm_p2__leds__buffer__scanner__run().
// (Protocol 2)
// -----------------------------------------------------------------------------

#include <Arduino.h>
#include "blm_boards__comm_p2__leds__buffer.h"
#include "blm_boards__comm_p2__leds__buffer__scanner__callbacks.h"
#include "debug_midi__arduino_serial.h"


/**
 * Finds dirty command for the given board and passes it to the appropriate callback.
 * @return true if the board became synchronized (clean), false otherwise
 */
static bool blm_boards__comm_p2__leds__buffer__scanner__scan(unsigned int board) {
    uint16_t dirty_commands = blm_boards__comm_p2__leds__buffer__commands__dirty[board];
    int index = __builtin_ffs(dirty_commands) - 1;
    if (index >= 0) {
        blm_boards__comm_p2__leds__buffer__scanner__emit_command(board, blm_boards__comm_p2__leds__buffer__commands[board][index]);
        dirty_commands &= ~(1U << (uint16_t) index);
        blm_boards__comm_p2__leds__buffer__commands__dirty[board] = dirty_commands;
        return dirty_commands == 0U;
    }
}


bool blm_boards__comm_p2__leds__buffer__scanner__is_runnable() {
    return blm_boards__comm_p2__leds__buffer__dirty;
}

void blm_boards__comm_p2__leds__buffer__scanner__run() {
    int board = __builtin_ffs(blm_boards__comm_p2__leds__buffer__dirty) - 1;
    if (board >= 0) {
        if (blm_boards__comm_p2__leds__buffer__scanner__scan(board)) {
            blm_boards__comm_p2__leds__buffer__dirty &= ~(1U << (uint32_t) board);
        }
    }
    // as optimisation, if all boards are clean, "suspend" the thread, and wake it up when LED updates are received.
    // (on the other hand, this check is quite fast anyway)
}
