#include <Arduino.h>
#include "midi_sender.h"
#include "midi_sender__arduino_serial.h"


int32_t readings[8];


#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
void setup() {
    for (int32_t & reading : readings) {
        reading = 0;
    }
    
    analogReadResolution(14);
  
    Serial1.begin(38400);
    midi_sender__arduino_serial__init(&Serial1);

    delay(200);
}
#pragma clang diagnostic pop


void read(int pin, int index, int channel) {
    auto reading = analogRead(pin);
    auto readingSigned = (int32_t) reading;
    auto prevReading = readings[index];
    auto diff = (readingSigned - prevReading);
    if (diff <= -64 || diff >= 64) {
        midi_sender__send_poly_pressure(channel, (reading >> 7U) & 0x7FU, reading & 0x7FU);
        readings[index] = readingSigned;
    }
}


#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
void loop() {
    read(A0, 0, 0x08);
    read(A1, 1, 0x09);
    read(A2, 2, 0x0A);
    read(A3, 3, 0x0B);
    read(A4, 4, 0x0C);
    read(A5, 5, 0x0D);
    read(A6, 6, 0x0E);
    read(A7, 7, 0x0F);
}
#pragma clang diagnostic pop
