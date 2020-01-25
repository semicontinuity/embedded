// Handles MIDI BLM LEDs control protocol:
//
// Update one: 9<row> <column> <colour>
//
// Update row: B<row> [00cc00hl] [pattern]
//   cc=color, 10=red, 01=green
//   h=1 for second half, 0 for first half
//   l=value for last led (8th or 16th)
//
// Update column: B<col> [00cc10hl] [pattern]
//   cc=color, 10=red, 01=green
//   h=1 for second half, 0 for first half
//   l=value for last led (8th or 16th)

#include <Arduino.h>

#include "midi_parser__callbacks__channel_msg.h"
#include "leds__updater.h"


static void blm_master__channel_msg_handler__process_single_led_change_event(midi_package_t midi_package) {
    uint8_t row = midi_package.chn;
    uint8_t column = midi_package.note;
    uint8_t colour = midi_package.velocity;
    leds__update_one(row, column, colour);
}


static void blm_master__channel_msg_handler__process_packed_leds_change_event(midi_package_t midi_package) {
    const uint8_t chn = midi_package.chn;
    const uint8_t cc_number = midi_package.cc_number;

    uint8_t pattern = midi_package.value;
    if (cc_number & 0x01U)   // means that 8th LED is on
        pattern |= (1U << 7U);

    const uint8_t is_second_half = cc_number & 0x02u;
    const uint8_t cc_number_masked = cc_number & 0xFCu;
    switch (cc_number_masked) {
        case 0x10:
#if BLM_SCALAR_NUM_COLOURS >= 2
            case 0x20:
#endif
            leds__update_row(chn, is_second_half, pattern, cc_number_masked == 0x10 ? 0 : 1 /* green or red */);  // or just shift to get color
            break;

        case 0x18:
#if BLM_SCALAR_NUM_COLOURS >= 2
            case 0x28:
#endif
            leds__update_column(chn, is_second_half, pattern, cc_number_masked == 0x18 ? 0 : 1 /* green or red */);   // or just shift to get color
            break;

        case 0x40:
#if BLM_SCALAR_NUM_COLOURS >= 2
            case 0x48:
#endif
            if (chn == 0) {
                leds__update_extra_column(is_second_half, pattern, cc_number_masked == 0x40 ? 0 : 1 /* green or red */);
            }
            break;

        case 0x60:
#if BLM_SCALAR_NUM_COLOURS >= 2
            case 0x68:
#endif
            if (chn == 0) {
                leds__update_extra_row(is_second_half, pattern, cc_number_masked == 0x60 ? 0 : 1 /* green or red */);
            } else if (chn == 15) {
                leds__update_extra(is_second_half, pattern,
                                   cc_number_masked == 0x60 ? 0 : 1 /* green or red */);
            }
            break;
    }
    
    // to generate pings:
    // notifyDataReceived();
}


void blm_master__channel_msg_handler__process(const midi_package_t &midi_package) {
    if (midi_package.event == NoteOff || midi_package.event == NoteOn) {
        // control the Duo-LEDs via Note On/Off Events
        // The colour is controlled with velocity value:
        // 0x00:       both LEDs off
        // 0x01..0x3f: green LED on
        // 0x40..0x5f: red LED on
        // 0x60..0x7f: both LEDs on
        blm_master__channel_msg_handler__process_single_led_change_event(midi_package);
    }
    else if (midi_package.event == CC) {
        // "check for packed format" which is transfered via CCs
        blm_master__channel_msg_handler__process_packed_leds_change_event(midi_package);
    }
}
