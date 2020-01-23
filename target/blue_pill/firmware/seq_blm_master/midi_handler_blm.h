#include <Arduino.h>

#include "midi_parser_callbacks__channel_msg.h"
#include "blm_boards_leds.h"


// 9<row> <column> <colour>
static void handle_single_led_change_event(midi_package_t midi_package) {
    uint8_t row = midi_package.chn;
    uint8_t column = midi_package.note;
    uint8_t colour = midi_package.velocity;
    blm_boards_leds__update_one(row, column, colour);
}


static void handle_packed_leds_change_event(midi_package_t midi_package) {
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
            blm_boards_leds__update_row(chn, is_second_half, pattern, cc_number_masked == 0x10 ? 0 : 1 /* green or red */);  // or just shift to get color
            break;

        case 0x18:
#if BLM_SCALAR_NUM_COLOURS >= 2
            case 0x28:
#endif
            blm_boards_leds__update_column(chn, is_second_half, pattern, cc_number_masked == 0x18 ? 0 : 1 /* green or red */);   // or just shift to get color
            break;

        case 0x40:
#if BLM_SCALAR_NUM_COLOURS >= 2
            case 0x48:
#endif
            if (chn == 0) {
                blm_boards_leds__update_extra_column(is_second_half, pattern, cc_number_masked == 0x40 ? 0 : 1 /* green or red */);
            }
            break;

        case 0x60:
#if BLM_SCALAR_NUM_COLOURS >= 2
            case 0x68:
#endif
            if (chn == 0) {
                blm_boards_leds__update_extra_row(is_second_half, pattern, cc_number_masked == 0x60 ? 0 : 1 /* green or red */);
            } else if (chn == 15) {
                blm_boards_leds__update_extra(is_second_half, pattern,
                                              cc_number_masked == 0x60 ? 0 : 1 /* green or red */);
            }
            break;
    }
    
    // to generate pings:
    // notifyDataReceived();
}


// Implementation of callbacks from midi_parser_callbacks__channel_msg
// -----------------------------------------------------------------------------

void midi_parser__on_channel_msg(midi_package_t midi_package) {
    if (midi_package.event == NoteOff || midi_package.event == NoteOn) {
        // control the Duo-LEDs via Note On/Off Events
        // The colour is controlled with velocity value:
        // 0x00:       both LEDs off
        // 0x01..0x3f: green LED on
        // 0x40..0x5f: red LED on
        // 0x60..0x7f: both LEDs on
        handle_single_led_change_event(midi_package);
    }
    else if (midi_package.event == CC) {
        // "check for packed format" which is transfered via CCs
        handle_packed_leds_change_event(midi_package);
    }
}
