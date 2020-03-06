// Scans LED state data structures
// and produces on BLM board LED update commands.
// May generate up to 1 LED update command on every invocation
// of blm_boards__comm_p1__leds__buffer__scanner__run().
// (Protocol 2)
// -----------------------------------------------------------------------------

#include <Arduino.h>
#include "blm_boards__comm_p2__leds__buffer.h"
#include "blm_boards__comm_p2__leds__buffer__scanner__callbacks.h"
#include "debug__arduino_serial_midi.h"



bool blm_boards__comm_p2__leds__buffer__scanner__is_runnable() {
    return blm_boards__comm_p2__leds__buffer__dirty;
}

void blm_boards__comm_p2__leds__buffer__scanner__run() {

}
