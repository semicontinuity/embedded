// =============================================================================
// Continuously reads 8 potentiometers and sends readings with MIDI messages.
// Used PolyPressure message (0xA) on channels 0-7 (or 8-F)
// with 14-bit payload (for greater precision) = 3 higher bits + 7 lower bits.
// =============================================================================
#include <stdint.h>
#include <Arduino.h>
#include "midi_sender.h"
#include "midi_sender__arduino_serial.h"

#define MIDI_CHANNEL_BASE 0x08

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
    Serial.begin(31250);
    midi_sender__arduino_serial__init(&Serial);
    delay(100);
}
#pragma clang diagnostic pop


void process(int pin, int index, int midiChannel) {
    auto reading = analogRead(pin);
    auto readingSigned = (int32_t) reading;
    auto prevReading = readings[index];
    auto diff = (readingSigned - prevReading);
    if (diff <= -4 || diff >= 4) {
        midi_sender__send_poly_pressure(midiChannel, (reading >> 7U) & 0x7FU, reading & 0x7FU);
        readings[index] = readingSigned;
    }
}


#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
void loop() {
    process(A0, 0, MIDI_CHANNEL_BASE + 0x00);
    process(A1, 1, MIDI_CHANNEL_BASE + 0x01);
    process(A2, 2, MIDI_CHANNEL_BASE + 0x02);
    process(A3, 3, MIDI_CHANNEL_BASE + 0x03);
    process(A0, 4, MIDI_CHANNEL_BASE + 0x04);
    process(A1, 5, MIDI_CHANNEL_BASE + 0x05);
    process(A2, 6, MIDI_CHANNEL_BASE + 0x06);
    process(A3, 7, MIDI_CHANNEL_BASE + 0x07);
}
#pragma clang diagnostic pop
