#include <Arduino.h>
#include <USBComposite.h>

#include "config.h"

#include "arduino_serial__reader.h"

static struct arduino_serial__reader midi__pot_1__reader {
        .arduino_serial     = &POT_READER_1_SERIAL_PORT,
        .process            = [](uint8_t b) { return (int) HOST_SERIAL_PORT.write(b); }
};

static struct arduino_serial__reader midi__pot_2__reader {
        .arduino_serial     = &POT_READER_2_SERIAL_PORT,
        .process            = [](uint8_t b) { return (int) HOST_SERIAL_PORT.write(b); }
};


void setup() {
    POT_READER_1_SERIAL_PORT.begin(POT_READER_1_SERIAL_BAUD_RATE);
    POT_READER_2_SERIAL_PORT.begin(POT_READER_2_SERIAL_BAUD_RATE);

    HardwareSerial *serial = &HOST_SERIAL_PORT;
    serial->begin(HOST_SERIAL_BAUD_RATE);
}


void loop() {
    if (arduino_serial__reader__is_runnable(&midi__pot_1__reader)) {
        arduino_serial__reader__run(&midi__pot_1__reader);
    }
    if (arduino_serial__reader__is_runnable(&midi__pot_2__reader)) {
        arduino_serial__reader__run(&midi__pot_2__reader);
    }
}
