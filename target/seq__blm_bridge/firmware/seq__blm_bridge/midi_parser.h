#define LC_INCLUDE "lc-addrlabels.h"
#include <Arduino.h>
#include <stdbool.h>
#include <pt.h>
#include "midi_package.h"


struct midi_parser {
    void (*on_channel_msg)(midi_package_t);
    void (*on_sysex_data)(uint8_t);
    void (*on_sysex_finish)();
    void (*on_sysex_error)();

    struct pt thread;
    uint8_t running_status;
    uint8_t first_payload_byte;
};


/**
 * Process incoming MIDI byte.
 * System realtime messages must be filtered.
 * System common messages are ignored.
 */
int midi_parser__process(struct midi_parser *p, uint8_t b) {
    struct pt *pt = &p->thread;
    PT_BEGIN(pt);

    if (b < 0x80) {
        PT_RESTART(pt); // discard bytes 00..7F, because running status byte is not defined yet
    }

    while (true) {
        if (b < 0xF0) {                 // Channel messages
            p->running_status = b;

            // channel messages payloads follow in groups of 1 or 2 bytes, depending on kind.
            while (true) {
                PT_YIELD(pt);           // Byte consumed, await next one

                if (b >= 0x80) {        // Valid payload byte must be < 0x80, it cannot be status byte!
                    // Current running status no longer applies
                    // Re-parse with this status byte at the beginning of the new message
                    break;
                }

                p->first_payload_byte = b;
                uint8_t second_payload_byte = 0;

                // messages 0xCx and 0xDx have highest 3 bits = 110; they have 1-byte payloads..
                if ((p->running_status & 0xE0U) != 0xC0U) {
                    PT_YIELD(pt);       // For other channel messages, read extra byte
                    if (b >= 0x80) {    // Valid payload byte must be < 0x80, it cannot be status byte!
                        break;          // Scrap current payload and re-parse with this byte at the beginning of the new message
                    }
                    second_payload_byte = b;
                }

                midi_package_t midi_package;
                midi_package.cin_cable = 0;
                midi_package.evnt0 = p->running_status;
                midi_package.evnt1 = p->first_payload_byte;
                midi_package.evnt2 = second_payload_byte;
                p->on_channel_msg(midi_package);
            }
        } else {
            // system common, system exclusive, or real-time messages

            if (b == 0xF0) {                // SYSEX start
                while (true) {              // Process SYSEX message
                    PT_YIELD(pt);           // Byte consumed, await another byte

                    if (b < 0x80) {
                        p->on_sysex_data(b);
                    } else {                // Any status byte (>= 0x80) terminates SYSEX message
                        if (b == 0xF7) {    // SYSEX END
                            p->on_sysex_finish();
                        } else {
                            p->on_sysex_error();
                        }
                        break;
                    }
                }
            }

            PT_RESTART(pt); // system common and system exclusive destroy running status, must ignore non-status bytes
        }
    }

    PT_END(pt);
}
