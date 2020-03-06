// Debug facility on top ove serial MIDI interface.
// Some overlap with midi_sender (but it does not provide SYSEX)
// -----------------------------------------------------------------------------

#ifndef __DEBUG_MIDI__ARDUINO_SERIAL
#define __DEBUG_MIDI__ARDUINO_SERIAL

#include <Arduino.h>
#include <stdbool.h>

#define D_BOARD             0x01
#define D_LED               0x02
#define D_SHIFT             0x03
#define D_MASK              0x04
#define D_PATTERN           0x05
#define D_ROW               0x06
#define D_COLUMN            0x07

#define D_CURRENT           0x10
#define D_REQUESTED         0x11
#define D_RAW_DIFF          0x14
#define D_GREEN_DIFF        0x15
#define D_RED_DIFF          0x16
#define D_DIFF              0x17
#define D_DIRTY             0x18

#define D_UPDATE_ONE        0x70
#define D_UPDATE_ROW        0x71
#define D_UPDATE_COLUMN     0x72
#define D_UPDATE_EX_ROW     0x73
#define D_UPDATE_EX_COLUMN  0x74
#define D_UPDATE_EX         0x75
#define D_SCAN              0x7F


static HardwareSerial *debug_midi__serial;


void debug_midi__serial__init(HardwareSerial *serial) {
    debug_midi__serial = serial;
}


void debug_midi__note_off(uint8_t channel, uint8_t note, uint8_t velocity) {
#if DEBUG_MIDI_NOTE_OFF
    debug_midi__serial->write(0x80 + channel);
    debug_midi__serial->write(note);
    debug_midi__serial->write(velocity);
#endif
}


void debug_midi__sysex_p0(uint8_t param) {
#if DEBUG_MIDI_SYSEX
    debug_midi__serial->write(0xf0);
    debug_midi__serial->write(param);
    debug_midi__serial->write(0xf7);
#endif
}

void debug_midi__sysex_p8(uint8_t param, uint8_t v) {
#if DEBUG_MIDI_SYSEX
    debug_midi__serial->write(0xf0);
    debug_midi__serial->write(param);
    debug_midi__serial->write((v >> 4) & 0x0F);
    debug_midi__serial->write(v & 0x0F);
    debug_midi__serial->write(0xf7);
#endif
}

void debug_midi__sysex_p16(uint8_t param, uint16_t v) {
#if DEBUG_MIDI_SYSEX
    debug_midi__serial->write(0xf0);
    debug_midi__serial->write(param);
    debug_midi__serial->write((v >> 12) & 0x0F);
    debug_midi__serial->write((v >> 8) & 0x0F);
    debug_midi__serial->write((v >> 4) & 0x0F);
    debug_midi__serial->write(v & 0x0F);
    debug_midi__serial->write(0xf7);
#endif
}

void debug_midi__sysex_p32(uint8_t param, uint32_t v) {
#if DEBUG_MIDI_SYSEX
    debug_midi__serial->write(0xf0);
    debug_midi__serial->write(param);
    debug_midi__serial->write((v >> 28) & 0x0F);
    debug_midi__serial->write((v >> 24) & 0x0F);
    debug_midi__serial->write((v >> 20) & 0x0F);
    debug_midi__serial->write((v >> 16) & 0x0F);
    debug_midi__serial->write((v >> 12) & 0x0F);
    debug_midi__serial->write((v >> 8) & 0x0F);
    debug_midi__serial->write((v >> 4) & 0x0F);
    debug_midi__serial->write(v & 0x0F);
    debug_midi__serial->write(0xf7);
#endif
}

#endif
