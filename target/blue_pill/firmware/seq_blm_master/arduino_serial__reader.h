#ifndef STREAM_PUMPER_H
#define STREAM_PUMPER_H

#include <stdint.h>
#include <HardwareSerial.h>

struct arduino_serial__reader {
    HardwareSerial *arduino_serial;
    int (*process)(uint8_t);
};


bool arduino_serial__reader__is_runnable(struct arduino_serial__reader *reader) {
    return reader->arduino_serial->available();
}

void arduino_serial__reader__run(struct arduino_serial__reader *reader) {
    reader->process(reader->arduino_serial->read());
}

#endif
