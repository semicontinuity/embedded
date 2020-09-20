// Unfinished.
// Problematic to get continuous group conversion working.

#include <Arduino.h>
#include "midi_sender.h"
#include "midi_sender__arduino_serial.h"
#include "analog_nonblocking2.h"

int32_t readings[8];

ADC_HandleTypeDef adc = {};

void setupAdc() {
    adc_init(adc, analogInputToPinName(0), 12);
    adc_pin_init(analogInputToPinName(0));
    adc_pin_init(analogInputToPinName(1));
    adc_pin_init(analogInputToPinName(2));
    adc_pin_init(analogInputToPinName(3));
//    adc_pin_init(analogInputToPinName(4));
//    adc_pin_init(analogInputToPinName(5));
//    adc_pin_init(analogInputToPinName(6));
//    adc_pin_init(analogInputToPinName(7));
    adc_channel_init(adc, analogInputToPinName(0), 1);
    adc_channel_init(adc, analogInputToPinName(1), 2);
    adc_channel_init(adc, analogInputToPinName(2), 3);
    adc_channel_init(adc, analogInputToPinName(3), 4);
//    adc_channel_init(adc, analogInputToPinName(4), 5);
//    adc_channel_init(adc, analogInputToPinName(5), 6);
//    adc_channel_init(adc, analogInputToPinName(6), 7);
//    adc_channel_init(adc, analogInputToPinName(7), 8);
    adc_calibrate(adc);
}

void setupReadings() {
    for (int32_t & reading : readings) {
        reading = 0;
    }
}


/*
static struct pt adc_reader__thread;

void adc_reader__init() {
    PT_INIT(&adc_reader__thread);
    adc_reader__init_readings();
    adc_reader__init_channels();
}

int adc_reader__thread__run() {
    struct pt *pt = &adc_reader__thread;
    PT_BEGIN(pt);

    while (true) {
        adc_reader__start_conversions();
        PT_YIELD(pt);
        adc_reader__process_readings();
    }

    PT_END(pt);
}
*/


#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
void setup() {
    setupAdc();

    adc_conversion_start(adc);

    setupReadings();

    analogReadResolution(14);
  
    Serial1.begin(38400);
    midi_sender__arduino_serial__init(&Serial1);

    delay(200);
}
#pragma clang diagnostic pop


void readNB(ADC_HandleTypeDef &AdcHandle, int index, int midiChannel) {
//    adc_init(AdcHandle, analogInputToPinName(0), 12);

//    while (adc_conversion_is_running(AdcHandle));
    adc_conversion_await(AdcHandle);

    auto reading = adc_conversion_get(AdcHandle);
//    adc_deinit(AdcHandle);

    auto readingSigned = (int32_t) reading;
    auto prevReading = readings[index];
    auto diff = (readingSigned - prevReading);
    if (diff <= -128 || diff >= 128) {
        midi_sender__send_poly_pressure(midiChannel, (reading >> 7U) & 0x7FU, reading & 0x7FU);
        readings[index] = readingSigned;
    }
}


#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
void loop() {
    readNB(adc, 0, 0x08);
    readNB(adc, 1, 0x09);
    readNB(adc, 2, 0x0a);
    readNB(adc, 3, 0x0b);
//    readNB(adcA1, 1, 0x09);
//    readNB(adcA2, 2, 0x0a);
//    readNB(adcA3, 3, 0x0b);

//    read(A0, 0, 0x08);
//    read(A1, 1, 0x09);
//    read(A2, 2, 0x0A);
//    read(A3, 3, 0x0B);
//    read(A4, 4, 0x0C);
//    read(A5, 5, 0x0D);
//    read(A6, 6, 0x0E);
//    read(A7, 7, 0x0F);
//    delay(500);
}
#pragma clang diagnostic pop
