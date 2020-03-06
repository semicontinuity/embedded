// Implements updating of multi-BLM LEDs data buffer
// for blm_master-style commands.
// (Protocol 2)
// -----------------------------------------------------------------------------

#include <Arduino.h>
#include <stdint.h>
#include "blm_master__leds.h"
#include "blm_boards__comm_p2__leds__buffer.h"
#include "debug_midi__arduino_serial.h"


// Implements blm_master__leds.h
// -----------------------------------------------------------------------------

void blm_boards__comm_p2__leds__buffer__blm_master__update_one(uint8_t row, uint8_t column, uint8_t color_code) {
}


void blm_boards__comm_p2__leds__buffer__blm_master__update_row(uint8_t row, uint8_t is_second_half, uint8_t pattern, uint8_t color_code) {
}


void blm_boards__comm_p2__leds__buffer__blm_master__update_column(uint8_t column, uint8_t is_second_half, uint8_t pattern, uint8_t color_code) {
}


void blm_boards__comm_p2__leds__buffer__blm_master__update_extra_row(uint8_t is_second_half, uint8_t pattern, uint8_t color_code) {
    debug_midi__sysex_p0(D_UPDATE_EX_ROW);
}


void blm_boards__comm_p2__leds__buffer__blm_master__update_extra_column(uint8_t is_second_half, uint8_t pattern, uint8_t color_code) {
    debug_midi__sysex_p0(D_UPDATE_EX_COLUMN);
}


void blm_boards__comm_p2__leds__buffer__blm_master__update_extra(uint8_t is_second_half, uint8_t pattern, uint8_t color_code) {
    debug_midi__sysex_p0(D_UPDATE_EX);
}
