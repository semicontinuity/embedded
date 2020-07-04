// Debug facility, implemented with the help of MIDI SYSEX messages.
// -----------------------------------------------------------------------------

#ifndef __DEBUG__MIDI_SYSEX
#define __DEBUG__MIDI_SYSEX

#include <Arduino.h>
#include <stdbool.h>
#include "midi_sender.h"


void debug__midi_sysex__p0(uint8_t param) {
#if DEBUG_MIDI_SYSEX
    midi_sender__send_sysex(&param, 1);
#endif
}

void debug__midi_sysex__p8(uint8_t param, uint8_t v) {
#if DEBUG_MIDI_SYSEX
    uint8_t payload[] = {
            param,
            static_cast<uint8_t>((v >> 4) & 0x0FU),
            static_cast<uint8_t>(v & 0x0FU)
    };
    midi_sender__send_sysex(payload, 3);
#endif
}

void debug__midi_sysex__p16(uint8_t param, uint16_t v) {
#if DEBUG_MIDI_SYSEX
    uint8_t payload[] = {
        param,
        static_cast<uint8_t>((v >> 12) & 0x0F),
        static_cast<uint8_t>((v >> 8) & 0x0F),
        static_cast<uint8_t>((v >> 4) & 0x0F),
        static_cast<uint8_t>(v & 0x0F),
    };
    midi_sender__send_sysex(payload, 5);
#endif
}

void debug__midi_sysex__p32(uint8_t param, uint32_t v) {
#if DEBUG_MIDI_SYSEX
    uint8_t payload[] = {
        static_cast<uint8_t>(param),
        static_cast<uint8_t>((v >> 28) & 0x0F),
        static_cast<uint8_t>((v >> 24) & 0x0F),
        static_cast<uint8_t>((v >> 20) & 0x0F),
        static_cast<uint8_t>((v >> 16) & 0x0F),
        static_cast<uint8_t>((v >> 12) & 0x0F),
        static_cast<uint8_t>((v >> 8) & 0x0F),
        static_cast<uint8_t>((v >> 4) & 0x0F),
        static_cast<uint8_t>(v & 0x0F),
    };
    midi_sender__send_sysex(payload, 9);
#endif
}

#endif
