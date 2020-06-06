#include <Arduino.h>
#include <stdint.h>
#include "blm_master__sysex_msg_handler__callbacks.h"
#include "blm_boards__comm__leds__palettes.h"

// Implementations of blm_master__sysex_msg_handler__callbacks.h
// -----------------------------------------------------------------------------

void blm_master__sysex_handler__handle_set_palette_data(uint8_t palette, uint8_t *data, int32_t length) {
    memcpy(&blm_boards__comm__leds__palettes[palette][0], data, length);
}
