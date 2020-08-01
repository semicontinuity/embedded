#include <Arduino.h>
#include "midi_sender.h"
#include "midi_sender__arduino_serial.h"
#include "analog_nonblocking.h"

int32_t readings[8];

ADC_HandleTypeDef adcA0 = {};
ADC_HandleTypeDef adcA1 = {};
ADC_HandleTypeDef adcA2 = {};
ADC_HandleTypeDef adcA3 = {};
ADC_HandleTypeDef adcA4 = {};
ADC_HandleTypeDef adcA5 = {};
ADC_HandleTypeDef adcA6 = {};
ADC_HandleTypeDef adcA7 = {};

void setupAdc() {
    adc_init(adcA0, analogInputToPinName(0), 12);
    adc_init(adcA1, analogInputToPinName(1), 12);
    adc_init(adcA2, analogInputToPinName(2), 12);
    adc_init(adcA3, analogInputToPinName(3), 12);
    adc_init(adcA4, analogInputToPinName(4), 12);
    adc_init(adcA5, analogInputToPinName(5), 12);
    adc_init(adcA6, analogInputToPinName(6), 12);
    adc_init(adcA7, analogInputToPinName(7), 12);
}

void setupReadings() {
    for (int32_t & reading : readings) {
        reading = 0;
    }
}


#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
void setup() {
    setupAdc();
    setupReadings();

    analogReadResolution(14);
  
    Serial1.begin(38400);
    midi_sender__arduino_serial__init(&Serial1);

    delay(200);
}
#pragma clang diagnostic pop


void read(int pin, int index, int channel) {
//    auto reading = analogRead(pin);
    auto pinName = analogInputToPinName(pin);
    ADC_HandleTypeDef AdcHandle = {};
    adc_init(AdcHandle, pinName, 12);

    auto reading = adc_read_value_blocking(pinName, 12);

    auto readingSigned = (int32_t) reading;
    auto prevReading = readings[index];
    auto diff = (readingSigned - prevReading);
    if (diff <= -64 || diff >= 64) {
        midi_sender__send_poly_pressure(channel, (reading >> 7U) & 0x7FU, reading & 0x7FU);
        readings[index] = readingSigned;
    }
}

void readNB(ADC_HandleTypeDef &AdcHandle, int index, int channel) {
    adc_conversion_start(AdcHandle);
    while (adc_conversion_is_running(AdcHandle));

    auto reading = adc_conversion_get(AdcHandle);
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
    readNB(adcA0, 0, 0x08);
    readNB(adcA1, 1, 0x09);
    readNB(adcA2, 2, 0x0a);
    readNB(adcA3, 3, 0x0b);

//    read(A0, 0, 0x08);
//    read(A1, 1, 0x09);
//    read(A2, 2, 0x0A);
//    read(A3, 3, 0x0B);
//    read(A4, 4, 0x0C);
//    read(A5, 5, 0x0D);
//    read(A6, 6, 0x0E);
//    read(A7, 7, 0x0F);
    delay(500);
}
#pragma clang diagnostic pop
