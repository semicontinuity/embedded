#include "midiXparser.h"
#include "midi_package.h"
#include "sysex_handler.h"

midiXparser midiSerial[SERIAL_INTERFACE_MAX];


void serial_midi_receiver__handle_non_sysex_message(midi_package_t p);


void serial_midi_receiver__process_sysex_message(uint8_t cable, midiXparser *xpMidi) {
    if (xpMidi->wasSysExMode()) {
        if (xpMidi->isSysExError()) {
            sysex__error();
        } else {
            sysex__finish();
        }
    } else {
        uint8_t b = xpMidi->getByte();
        if (b != 0xf0) {
            sysex__data(b);
        }
    }
}

void serial_midi_receiver__process_non_sysex_message(uint8_t cable, midiXparser *xpMidi) {
    midi_package_t p {.ALL = 0};
    p.cin_cable = cable << 4;

    uint8_t msgLen = xpMidi->getMidiMsgLen();
    uint8_t msgType = xpMidi->getMidiMsgType();

    p.cin_cable = cable << 4;
    memcpy(&p.evnt0, &(xpMidi->getMidiMsg()[0]), msgLen);

    // Real time single byte message CIN F->
    if (msgType == midiXparser::realTimeMsgTypeMsk) p.cin_cable += 0xF;
    else

        // Channel voice message => CIN A-E
    if (msgType == midiXparser::channelVoiceMsgTypeMsk)
        p.cin_cable += ((xpMidi->getMidiMsg()[0]) >> 4);
    else

        // System common message CIN 2, 3 or 5
    if (msgType == midiXparser::systemCommonMsgTypeMsk) {
        // 5 -  single-byte system common message (Tune request is the only case)
        if (msgLen == 1) p.cin_cable += 5;

            // 2/3 - two/three bytes system common message
        else p.cin_cable += msgLen;
    } else return; // We should never be here !

    serial_midi_receiver__handle_non_sysex_message(p);
}


void serial_midi_receiver__init(void) {
    Serial2.begin(31250);
    midiSerial[1].setMidiMsgFilter(midiXparser::allMsgTypeMsk);
}

void serial_midi_receiver__run() {
    if (Serial2.available()) {
        midiSerial[1].parse(Serial2.read());
        if (midiSerial[1].getMidiMsgType() == midiXparser::sysExMsgTypeMsk) {
            serial_midi_receiver__process_sysex_message(1, &midiSerial[1]);
        } else {
            // Not a sysex. The message is complete.
            serial_midi_receiver__process_non_sysex_message(1, &midiSerial[1]);
        }
    }
}
