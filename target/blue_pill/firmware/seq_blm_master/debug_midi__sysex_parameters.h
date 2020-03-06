#ifndef __DEBUG_MIDI__SYSEX_PARAMETERS
#define __DEBUG_MIDI__SYSEX_PARAMETERS

#define D_BOARD             0x01
#define D_LED               0x02
#define D_SHIFT             0x03
#define D_MASK              0x04
#define D_PATTERN           0x05
#define D_ROW               0x06
#define D_COLUMN            0x07

#define D_CURRENT           0x10
#define D_REQUESTED         0x11
#define D_RAW_DIFF          0x14
#define D_GREEN_DIFF        0x15
#define D_RED_DIFF          0x16
#define D_DIFF              0x17
#define D_DIRTY             0x18

#define D_UPDATE_ONE        0x70
#define D_UPDATE_ROW        0x71
#define D_UPDATE_COLUMN     0x72
#define D_UPDATE_EX_ROW     0x73
#define D_UPDATE_EX_COLUMN  0x74
#define D_UPDATE_EX         0x75
#define D_SCAN              0x7F

#endif
