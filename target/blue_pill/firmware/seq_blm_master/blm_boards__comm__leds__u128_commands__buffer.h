// LED state data structures tuned for updates of 16 4x4 boards of RGB LEDs.
// BLM Board supports updating a LED with a 2-byte UNPACK128 I2C command, with 7-bit indexed color payload.
// For every board, there are 16 LED.
// So, in total, there are 16 * 16 pending commands possible.
// Per LED, only the latest command is stored,
// but it should be OK, because I2C commands are sent faster than MIDI commands are received.
// ---------------------------------------------------------------------------------------------------------------------------------

#ifndef __BLM_BOARDS__COMM__LEDS__U128_COMMANDS__BUFFER
#define __BLM_BOARDS__COMM__LEDS__U128_COMMANDS__BUFFER

#include <stdint.h>
#include "debug_midi__arduino_serial.h"
#include "debug_midi__sysex_parameters.h"


uint8_t  blm_boards__comm__leds__u128_commands__buffer__colors[16][16];         // every entry is a 1-byte indexed color to be sent to a board
uint16_t blm_boards__comm__leds__u128_commands__buffer__commands__pending[16];  // 1 bit means that corresponding command for the board is pending
uint16_t blm_boards__comm__leds__u128_commands__buffer__boards_dirty;           // 1 bit means that corresponding board has pending commands


void blm_boards__comm__leds__u128_commands__buffer__init() {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            blm_boards__comm__leds__u128_commands__buffer__colors[i][j] = 0U;
        }
    }
    for (int i = 0; i < 16; i++) {
        blm_boards__comm__leds__u128_commands__buffer__commands__pending[i] = 0U;
    }
    blm_boards__comm__leds__u128_commands__buffer__boards_dirty = 0U;
}


static void blm_boards__comm__leds__u128_commands__buffer__put(uint8_t matrix, uint8_t led, uint8_t color) {
    debug_midi__sysex_p8(D_BOARD, matrix);
    blm_boards__comm__leds__u128_commands__buffer__colors[matrix][led] = color;
    blm_boards__comm__leds__u128_commands__buffer__commands__pending[matrix] |= (1U << led);
}


#endif
