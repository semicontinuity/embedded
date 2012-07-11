#ifndef __KEYBOARD_CONNECTION_H
#define __KEYBOARD_CONNECTION_H

#define outputScanValue(v)  PORTB=(v)
#define inputScanValue()    (PINB)

#define keyboard_init() { DDRB = 0xF0; PORTB = 0xFF; }

#endif