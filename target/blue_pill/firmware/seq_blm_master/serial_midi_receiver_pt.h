#define LC_INCLUDE "lc-addrlabels.h"
#include <Arduino.h>
#include <stdbool.h>
#include <pt.h>
#include "sysex_handler.h"

static struct pt task_midi_receiver__thread;

void serial_midi_receiver__init() {
    Serial2.begin(31250);
    PT_INIT(&task_midi_receiver__thread);
}

bool serial_midi_receiver__is_runnable() {
    return Serial2.available();
}


int serial_midi_receiver__run() {
    struct pt *pt = &task_midi_receiver__thread;
    PT_BEGIN(pt);
    for (;;) {
        uint8_t first = Serial2.read();
        if (first != 0xF0) PT_RESTART(pt);

        uint8_t b;
        while (true) {
            PT_YIELD(pt);
            b = Serial2.read();

            if (b >= 0x80) break;
            sysex__data(b);
        }

        if (b == 0xF7) {
            sysex__finish();
        } else {
            sysex__error();
        }

        PT_RESTART(pt);
    }
    PT_END(pt);
}
