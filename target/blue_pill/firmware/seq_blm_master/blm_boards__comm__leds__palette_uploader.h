// Palette uploader with area to keep 16 palettes.
//
// When a request to change palette arrives, 'requested_palette' is set to the requested palette number.
// Then, palette is uploaded to multiple boards when I2C bus becomes free, this is time-consuming.
// There is no queue for palette change commands,
// it is assumed that they are issued extremely rarely, when the device is initialized.
// ---------------------------------------------------------------------------------------------------------------------------------

#ifndef __BLM_BOARDS__COMM__LEDS__PALETTE_UPLOADER
#define __BLM_BOARDS__COMM__LEDS__PALETTE_UPLOADER

#include <stdint.h>
#include <Arduino.h>
#include <Wire.h>
#include "seq_blm_master__config.h"


uint8_t blm_boards__comm__leds__palette_uploader__palettes[16][128 * 3];
int8_t blm_boards__comm__leds__palette_uploader__requested_palette;

static TwoWire *blm_boards__comm__leds__palette_uploader__wire;
static uint8_t blm_boards__comm__leds__palette_uploader__base_address;


void blm_boards__comm__leds__palette_uploader__init(TwoWire *wire, uint8_t base_address) {
    blm_boards__comm__leds__palette_uploader__wire = wire;
    blm_boards__comm__leds__palette_uploader__base_address = base_address;
    blm_boards__comm__leds__palette_uploader__requested_palette = -1;
}

void blm_boards__comm__leds__palette_uploader__request(uint8_t palette) {
    blm_boards__comm__leds__palette_uploader__requested_palette = palette;
}

/**
 * Upload the specified palette to the specified board.
 * Because I2C payload size is limited by Wire library, do multiple (16) uploads, each carrying data for 8 entries.
 */
void blm_boards__comm__leds__palette_uploader__upload(uint8_t board, uint8_t palette) {
    for (int entry = 0; entry < 128; entry += 8) {
        blm_boards__comm__leds__palette_uploader__wire->beginTransmission(blm_boards__comm__leds__palette_uploader__base_address + board);
        blm_boards__comm__leds__palette_uploader__wire->write(0x80 + entry);    // WRITE_PALETTE_MEMORY command
        blm_boards__comm__leds__palette_uploader__wire->write(&blm_boards__comm__leds__palette_uploader__palettes[palette][entry * 3], 8 * 3);
        blm_boards__comm__leds__palette_uploader__wire->endTransmission();
    }
}

bool blm_boards__comm__leds__palette_uploader__is_runnable() {
    return blm_boards__comm__leds__palette_uploader__requested_palette >= 0;
}

void blm_boards__comm__leds__palette_uploader__run() {
    for (uint8_t board = 0; board < BLM_SCALAR_NUM_BOARDS; board++) {
        blm_boards__comm__leds__palette_uploader__upload(board, blm_boards__comm__leds__palette_uploader__requested_palette);
    }
    blm_boards__comm__leds__palette_uploader__requested_palette = -1;
}


#endif
