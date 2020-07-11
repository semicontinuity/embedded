// Palette buffer with area to keep 16 palettes.
// ---------------------------------------------------------------------------------------------------------------------------------

#ifndef __BLM_BOARDS__COMM__LEDS__PALETTE_BUFFER
#define __BLM_BOARDS__COMM__LEDS__PALETTE_BUFFER

#include <stdint.h>
#include <Arduino.h>
#include "seq__blm_bridge__config.h"

uint8_t blm_boards__comm__leds__palette__buffer__palettes[16][128 * 3];


void blm_boards__comm__leds__palette__buffer__palettes__set_palette_data(uint8_t palette, uint8_t *data, int32_t length) {
    memcpy(&blm_boards__comm__leds__palette__buffer__palettes[palette][0], data, length);
}

#endif
