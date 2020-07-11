// Handles MIDI BLM LEDs control protocol (see blm_scalar/README.txt), with ACCENT and PRESENT extensions.
// Note, that CHANNEL field is used by this protocol, therefore, only one BLM_MASTER device can reside on the MIDI port.
//
// Select palette: 0xC[MMMM] [0sRCpppp] - implemented with Program change messages
//   p=palette number, 0-15
//   s=specific matrix flag (proposed): s=0: update palette on all matrices; s=1: update palette on specific matrix
//   R=extra row flag (proposed)
//   C=extra column flag
//   MMMM=matrix number
//
// Update single LED messages - implemented with NoteOn/NoteOff messages
//
// Accent single LED: 0xD<row> [0Akk<column>] (channel pressure)
//   A=accent; 1=accent on, 0=accent off
//   kk=kind; 00=LED from main 16x16 matrix; 01=LED from extra rows; 10=LED from extra columns, 11=LED from extra LEDs
//
// Update one LED:               9<row> <column>    <colour>
// Update one extra-column LED : 9<row> <40+column> <colour>
// Update one extra-row LED :    90     <60+column> <colour>
// Update one extra LED :        9F     <60+led>    <colour>
//   Colors: 0x00: both LEDs off, 0x01..0x3f: green LED on, 0x40..0x5f: red LED on, 0x60..0x7f: both LEDs on
//
// Multi-LED update commands (packed format) - implemented with Change Control messages
//
// Update row: B<row> [00cc0Ahl] [pattern]
//   cc=color, 10=red, 01=green
//   A=accent, 1 if it is accent pattern
//   h=1 for second half, 0 for first half
//   l=value for last led (8th or 16th)
//
// Update extra row: B0 [0110cAhl] [pattern]
//   c=color, 1=red, 0=green
//   A=accent, 1 if it is accent pattern
//   h=1 for second half, 0 for first half
//   l=value for last led (8th or 16th)
//
// Update column: B<col> [00cc1Ahl] [pattern]
//   cc=color, 10=red, 01=green
//   A=accent, 1 if it is accent pattern
//   h=1 for second half, 0 for first half
//   l=value for last led (8th or 16th)
//
// Update extra column: B0 [0100cAhl] [pattern]
//   c=color, 1=red, 0=green
//   A=accent, 1 if it is accent pattern
//   h=1 for second half, 0 for first half
//   l=value for last led (8th or 16th)
//
// Update extra LEDs: BF [0110cA0l] [pattern]
//   c=color, 1=red, 0=green
//   A=accent, 1 if it is accent pattern
//   l=value for 8th led

#include <Arduino.h>

#include "seq_blm_bridge__config.h"
#include "host__leds_msg.h"
#include "midi_package.h"


static void host__channel_msg_handler__process_select_palette_event(midi_package_t midi_package) {
    uint8_t palette = midi_package.program_change & 0x0FU;
    host__leds_msg__select_palette(palette);
}

static void host__channel_msg_handler__process_single_led_color_event(midi_package_t midi_package) {
    uint8_t row = midi_package.chn;
    uint8_t column = midi_package.note;
    uint8_t color = midi_package.velocity;
    host__leds_msg__update_color(row, column, color);
}

static void host__channel_msg_handler__process_single_led_change_event(midi_package_t midi_package) {
    uint8_t row = midi_package.chn;
    uint8_t column = midi_package.note;
    uint8_t color = midi_package.velocity;
    host__leds_msg__update_one(row, column, color);
}


static void host__channel_msg_handler__process_packed_leds_change_event(midi_package_t midi_package) {
    const uint8_t chn = midi_package.chn;
    const uint8_t cc_number = midi_package.cc_number;

    uint8_t pattern = midi_package.value;
    if (cc_number & 0x01U)   // means that 8th LED is on
        pattern |= (1U << 7U);

    const uint8_t is_second_half = cc_number & 0x02u;
    const uint8_t cc_number_masked = cc_number & 0xFCu;
    switch (cc_number_masked) {
        case 0x10:
#if NUM_COLOURS >= 2
        case 0x20:
#endif
            host__leds_msg__update_row(chn, is_second_half, pattern,
                                       cc_number_masked == 0x10 ? 0 : 1 /* green or red */);
            break;

        case 0x18:
#if NUM_COLOURS >= 2
        case 0x28:
#endif
            host__leds_msg__update_column(chn, is_second_half, pattern,
                                          cc_number_masked == 0x18 ? 0 : 1 /* green or red */);
            break;

        case 0x40:
#if NUM_COLOURS >= 2
        case 0x48:
#endif
            if (chn == 0) {
                host__leds_msg__update_extra_column(is_second_half, pattern,
                                                    cc_number_masked == 0x40 ? 0 : 1 /* green or red */);
            }
            break;

        case 0x60:
#if NUM_COLOURS >= 2
        case 0x68:
#endif
            if (chn == 0) {
                host__leds_msg__update_extra_row(is_second_half, pattern,
                                                 cc_number_masked == 0x60 ? 0 : 1 /* green or red */);
            } else if (chn == 15) {
                host__leds_msg__update_extra(is_second_half, pattern,
                                             cc_number_masked == 0x60 ? 0 : 1 /* green or red */);
            }
            break;
        default:
            break;
    }
}


void host__channel_msg_handler__process(const midi_package_t &midi_package) {
    if (midi_package.event == NoteOff || midi_package.event == NoteOn) {
        // control the LEDs with Note On/Off Events
        // The colour is controlled with velocity value:
        // 0x00:       both LEDs off
        // 0x01..0x3f: green LED on
        // 0x40..0x5f: red LED on
        // 0x60..0x7f: both LEDs on
        host__channel_msg_handler__process_single_led_change_event(midi_package);
    } else if (midi_package.event == CC) {
        host__channel_msg_handler__process_packed_leds_change_event(midi_package);
    } else if (midi_package.event == PolyPressure) {
        host__channel_msg_handler__process_single_led_color_event(midi_package);
    } else if (midi_package.event == ProgramChange) {
        host__channel_msg_handler__process_select_palette_event(midi_package);
    }
}
