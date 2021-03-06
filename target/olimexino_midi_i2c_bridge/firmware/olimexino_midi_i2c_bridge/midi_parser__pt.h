#define LC_INCLUDE "lc-addrlabels.h"
#include <Arduino.h>
#include <stdbool.h>
#include <pt.h>
#include "midi_parser.h"
#include "midi_package.h"
#include "midi_parser__callbacks__channel_msg.h"
#include "midi_parser__callbacks__sysex_msg.h"


// Implementation of midi_parser.h

static struct pt midi_parser__thread;
static uint8_t midi_parser__running_status;
static uint8_t midi_parser__byte;


void midi_parser__init() {
    PT_INIT(&midi_parser__thread);
}


// no REALTIME support
int midi_parser__process(uint8_t b) {
    struct pt *pt = &midi_parser__thread;
    PT_BEGIN(pt);

    if (b < 0x80) {
        PT_RESTART(pt); // discard bytes 00..7F, because running status byte is not defined yet
    }

    while (true) {
        if (b < 0xF0) {
            // channel messages payloads follow in groups of 1 or 2 bytes, depending on kind
            midi_parser__running_status = b;

            while (true) {
                PT_YIELD(pt);
                if (b >= 0x80) break;   // scrap current payload and re-parse as with this byte as beginning of the message

                midi_parser__byte = b;
                uint8_t p1 = 0;

                // messages 0xCx and 0xDx have highest 3 bits = 110; they have 1-byte payloads..
                if ((midi_parser__running_status & 0xE0U) != 0xC0U) {
                    // for other messages, read extra byte
                    PT_YIELD(pt);
                    if (b >= 0x80) break;   // scrap current payload and re-parse as with this byte as beginning of the message
                    p1 = b;
                }

                midi_package_t midi_package;
                midi_package.cin_cable = 0;
                midi_package.evnt0 = midi_parser__running_status;
                midi_package.evnt1 = midi_parser__byte;
                midi_package.evnt2 = p1;
                midi_parser__on_channel_msg(midi_package);
            }
        } else {
            // system common, system exclusive, or real-time messages

            if (b == 0xF0) {    // sysex start
                while (true) {
                    PT_YIELD(pt);
                    if (b < 0x80) {
                        midi_parser__on_sysex_data(b);
                    } else {
                        if (b == 0xF7) {
                            midi_parser__on_sysex_finish();
                        } else {
                            midi_parser__on_sysex_error();
                        }
                        break;
                    }
                }
            }

            PT_RESTART(pt); // system common and system exclusive destroy running status
        }
    }

    PT_END(pt);
}
