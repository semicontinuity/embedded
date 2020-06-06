// Collection of palette data.
//
// When a request to change palette arrives, 'requested' is set to the requested palette number.
// There is no queue for palette change commands, it is assumed that they are issued extremely rarely,
// when the device is initialized.
// ---------------------------------------------------------------------------------------------------------------------------------

#ifndef __BLM_BOARDS__COMM__LEDS__PALETTES
#define __BLM_BOARDS__COMM__LEDS__PALETTES

#include <stdint.h>
#include <Arduino.h>
#include <Wire.h>


uint8_t blm_boards__comm__leds__palettes[16][128 * 3];
volatile int8_t blm_boards__comm__leds__palettes__requested = -1;

static TwoWire *blm_boards__comm__leds__palettes__wire;
static uint8_t blm_boards__comm__leds__palettes__base_address;


void blm_boards__comm__leds__palettes__init(TwoWire *wire, uint8_t base_address) {
    blm_boards__comm__leds__palettes__wire = wire;
    blm_boards__comm__leds__palettes__base_address = base_address;
}

void blm_boards__comm__leds__palettes__request(uint8_t palette) {
    blm_boards__comm__leds__palettes__requested = palette;
}

void blm_boards__comm__leds__palettes__upload(uint8_t board, uint8_t palette) {
    if (board < BLM_SCALAR_NUM_BOARDS) {
        blm_boards__comm__leds__palettes__wire->beginTransmission(blm_boards__comm__leds__palettes__base_address + board);
        blm_boards__comm__leds__palettes__wire->write(0x80);
        blm_boards__comm__leds__palettes__wire->write(&blm_boards__comm__leds__palettes[palette][0], 128*3);
        blm_boards__comm__leds__palettes__wire->endTransmission();
    }
}

#endif
