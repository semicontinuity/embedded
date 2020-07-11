// Structs are the same as in MIOS32 (https://github.com/midibox/mios32),

#ifndef __MIDI_PACKAGE_H
#define __MIDI_PACKAGE_H

#include <stdint.h>

// CIN values from USB MIDI spec (in some way, redundant info):
//
// CIN  MIDI_X size     Description
// 0x0  1, 2 or 3       Miscellaneous function codes. Reserved for future extensions.
// 0x1  1, 2 or 3       Cable events. Reserved for future expansion.
// 0x2  2               Two-byte System Common messages like MTC, SongSelect, etc.
// 0x3  3               Three-byte System Common messages like SPP, etc.
// 0x4  3               SysEx starts or continues
// 0x5  1               Single-byte System Common Message or SysEx ends with following single byte.
// 0x6  2               SysEx ends with following two bytes.
// 0x7  3               SysEx ends with following three bytes.
// 0x8  3               Note-off
// 0x9  3               Note-on
// 0xA  3               Poly-KeyPress
// 0xB  3               Control change
// 0xC  2               Program change
// 0xD  2               Channel pressure
// 0xE  3               PitchBend change
// 0xF  1               Single byte


typedef enum {
    NoteOff       = 0x8,
    NoteOn        = 0x9,
    PolyPressure  = 0xa,
    CC            = 0xb,
    ProgramChange = 0xc,
    Aftertouch    = 0xd,
    PitchBend     = 0xe
} midi_event_t;


typedef enum {
    Chn1,
    Chn2,
    Chn3,
    Chn4,
    Chn5,
    Chn6,
    Chn7,
    Chn8,
    Chn9,
    Chn10,
    Chn11,
    Chn12,
    Chn13,
    Chn14,
    Chn15,
    Chn16
} midi_chn_t;


typedef union {
    struct {
        uint32_t ALL;
    };
    struct {
        uint8_t cin_cable;
        uint8_t evnt0;
        uint8_t evnt1;
        uint8_t evnt2;
    };
    struct {
        uint8_t type:4;
        uint8_t cable:4;
        uint8_t chn:4;   // midi_chn_t
        uint8_t event:4; // midi_event_t
        uint8_t value1;
        uint8_t value2;
    };

    // C++ doesn't allow to redefine names in anonymous unions
    // as a simple workaround, we rename these redundant names
    struct {
        uint8_t cin:4;
        uint8_t dummy1_cable:4;
        uint8_t dummy1_chn:4;    // midi_chn_t
        uint8_t dummy1_event:4;  // midi_event_t
        uint8_t note:8;
        uint8_t velocity:8;
    };
    struct {
        uint8_t dummy2_cin:4;
        uint8_t dummy2_cable:4;
        uint8_t dummy2_chn:4;    // midi_chn_t
        uint8_t dummy2_event:4;  // midi_event_t
        uint8_t cc_number:8;
        uint8_t value:8;
    };
    struct {
        uint8_t dummy3_cin:4;
        uint8_t dummy3_cable:4;
        uint8_t dummy3_chn:4;    // midi_chn_t
        uint8_t dummy3_event:4;  // midi_event_t
        uint8_t program_change:8;
        uint8_t dummy3:8;
    };
} midi_package_t;

#endif
