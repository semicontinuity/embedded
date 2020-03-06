// Debug facility on top ove serial MIDI interface.
// Some overlap with midi_sender (but it does not provide SYSEX)
// -----------------------------------------------------------------------------

#ifndef __DEBUG_MIDI__ARDUINO_SERIAL
#define __DEBUG_MIDI__ARDUINO_SERIAL

#include <Arduino.h>
#include <stdbool.h>


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

void debug_midi__aftertouch(uint8_t channel, uint8_t note, uint8_t pressure) {
#if DEBUG_MIDI_NOTE_OFF
    debug_midi__serial->write(0xA0 + channel);
    debug_midi__serial->write(note);
    debug_midi__serial->write(pressure);
#endif
}

void debug_midi__control_change(uint8_t channel, uint8_t number, uint8_t value) {
#if DEBUG_MIDI_NOTE_OFF
    debug_midi__serial->write(0xB0 + channel);
    debug_midi__serial->write(number);
    debug_midi__serial->write(value);
#endif
}

void debug_midi__program_change(uint8_t channel, uint8_t value) {
#if DEBUG_MIDI_NOTE_OFF
    debug_midi__serial->write(0xC0 + channel);
    debug_midi__serial->write(value);
#endif
}

void debug_midi__channel_pressure(uint8_t channel, uint8_t value) {
#if DEBUG_MIDI_NOTE_OFF
    debug_midi__serial->write(0xD0 + channel);
    debug_midi__serial->write(value);
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
