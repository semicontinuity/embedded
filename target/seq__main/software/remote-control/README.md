Scripts for remote control of MIDIBox SEQ v4+

SYSEX messages:


SEQ_MIDI_SYSEX_REMOTE_Server_Mode
====================================

Message format:

HEADER  0xf0, 0x00, 0x00, 0x7e, 0x4d
DEV_ID  0x00
REMOTE  0x09
SET_MODE    0x00
MODE    0xXX
FOOTER  0xf7

MODE: 1=server


SEQ_MIDI_SYSEX_REMOTE_Server_SendLCD
====================================

Message format:

HEADER  0xf0, 0x00, 0x00, 0x7e, 0x4d
DEV_ID  0x00
REMOTE  0x09
LCD     0x02
X       0xXX
Y       0xYY
DATA    0xDD
FOOTER  0xf7

NB: data bytes have the topmost bit unset


SEQ_MIDI_SYSEX_REMOTE_Server_SendLED
====================================

Message format:

HEADER  0xf0, 0x00, 0x00, 0x7e, 0x4d
DEV_ID  0x00
REMOTE  0x09
LED     0x04
FIRST   0xXX
DATA    0xDD
FOOTER  0xf7

NB:
* FIRST is first_sr*2
* DATA contains nibble bytes: for each SR, the is lower-nibble byte and higher-nibble byte


SEQ_MIDI_SYSEX_REMOTE_Server_SendCharset
====================================

Message format:

HEADER  0xf0, 0x00, 0x00, 0x7e, 0x4d
DEV_ID  0x00
REMOTE  0x09
CHARSET 0x03
CS      0xXX
FOOTER  0xf7



Example sysex messages to render text on LCD
============================================

f0 00 00 7e 4d 00 09 00 02 f7
f0 00 00 7e 4d 00 09 02 00 00 40 40 40 40 f7


Query parameters
============================================
0xf0, 0x00, 0x00,  0x7e, 0x32, 0x00,  0x00, PARAM, 0xf7
PARAM: 0-9
