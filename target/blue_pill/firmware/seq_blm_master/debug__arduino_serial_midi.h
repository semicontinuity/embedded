// Scans LED state data structures
// and produces on BLM board LED update commands.
// May generate up to 1 LED update command on every invocation
// of blm_boards_leds__state_scanner__run().
// -----------------------------------------------------------------------------

#ifndef __DEBUG__ARDUINO_SERIAL_MIDI
#define __DEBUG__ARDUINO_SERIAL_MIDI

#include <Arduino.h>
#include <stdbool.h>
#include "blm_boards_leds__state.h"
#include "blm_boards_leds__state_scanner_callbacks.h"

#define D_BOARD         0x01
#define D_LED           0x02
#define D_SHIFT         0x03
#define D_MASK          0x04
#define D_CURRENT       0x10
#define D_REQUESTED     0x11
#define D_RAW_DIFF      0x14
#define D_GREEN_DIFF    0x15
#define D_RED_DIFF      0x16
#define D_DIFF          0x17
#define D_DIRTY         0x18

#define D_UPDATE_ONE    0x70
#define D_UPDATE_ROW    0x71
#define D_SCAN          0x7F


void debug_p0(uint8_t param) {
    Serial2.write(0xf0);
    Serial2.write(param);
    Serial2.write(0xf7);
}

void debug_p8(uint8_t param, uint8_t v) {
    Serial2.write(0xf0);
    Serial2.write(param);
    Serial2.write((v >> 4) & 0x0F);
    Serial2.write(v & 0x0F);
    Serial2.write(0xf7);
}


void debug_p16(uint8_t param, uint16_t v) {
    Serial2.write(0xf0);
    Serial2.write(param);
    Serial2.write((v >> 12) & 0x0F);
    Serial2.write((v >> 8) & 0x0F);
    Serial2.write((v >> 4) & 0x0F);
    Serial2.write(v & 0x0F);
    Serial2.write(0xf7);
}

void debug_p32(uint8_t param, uint32_t v) {
    Serial2.write(0xf0);
    Serial2.write(param);
    Serial2.write((v >> 28) & 0x0F);
    Serial2.write((v >> 24) & 0x0F);
    Serial2.write((v >> 20) & 0x0F);
    Serial2.write((v >> 16) & 0x0F);
    Serial2.write((v >> 12) & 0x0F);
    Serial2.write((v >> 8) & 0x0F);
    Serial2.write((v >> 4) & 0x0F);
    Serial2.write(v & 0x0F);
    Serial2.write(0xf7);
}

#endif
