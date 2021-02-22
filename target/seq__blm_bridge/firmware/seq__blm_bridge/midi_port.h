#ifndef __MIDI_PORT_H
#define __MIDI_PORT_H


typedef enum {
    MIDI_PORT_UNDEFINED = 0x00,
    MIDI_PORT_USB       = 0x10,
    MIDI_PORT_SERIAL_1  = 0x20
} midi_port_t;


#endif
