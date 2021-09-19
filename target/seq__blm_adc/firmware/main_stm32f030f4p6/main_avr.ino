// =============================================================================
// Continuously reads 8 potentiometers and sends readings with MIDI messages.
//
// Option A:
// Used PolyPressure message (0xA) on channels 0-7 (or 8-F)
// with 14-bit payload (for greater precision) = 3 higher bits + 7 lower bits.
//
// Option B: MidiBox protocol (CC messages on midi channels 0-7 or 8-F)
// =============================================================================
#include <stdint.h>
#include <Arduino.h>
#include "midi_sender.h"
#include "midi_sender__arduino_serial.h"

#define MIDI_CHANNEL_BASE 0x00

int32_t readings[8];


void setupReadings() {
    for (int32_t & reading : readings) {
        reading = 0;
    }
}


#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
void setup() {
    setupReadings();

    Serial.setRx(PA10); // important! by default, RX is on another pin
    Serial.setTx(PA9);  // important! by default, RX is on another pin

    Serial.begin(31250/*38400*/);
    midi_sender__arduino_serial__init(&Serial);
    delay(100);
}
#pragma clang diagnostic pop


void process(int pin, int control) {
    auto reading = analogRead(pin);
    auto readingSigned = (int32_t) reading;
    auto prevReading = readings[control];
    auto diff = (readingSigned - prevReading);
    if (diff <= -4 || diff >= 4) {
        // up to 14-bit presision
//        midi_sender__send_poly_pressure(MIDI_CHANNEL_BASE + control, (reading >> 7U) & 0x7FU, reading & 0x7FU);

        // 7-bit precision, MIDIBox protocol: number of fader encoded int midi channel number.
        midi_sender__send_control_change(MIDI_CHANNEL_BASE + control, 0x01U, reading >> 03U);
        readings[control] = readingSigned;
    }
}


#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
void loop() {
    process(A0, 0x00);
    process(A1, 0x01);
    process(A2, 0x02);
    process(A3, 0x03);
    process(A4, 0x04);
    process(A5, 0x05);
    process(A6, 0x06);
    process(A7, 0x07);
}
#pragma clang diagnostic pop
