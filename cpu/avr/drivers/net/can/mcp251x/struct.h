#ifndef __CPU__AVR__DRIVERS__NET__MCP251X__STRUCT_H
#define __CPU__AVR__DRIVERS__NET__MCP251X__STRUCT_H

#include <stdint.h>

// Useful structure definitions
// Reminder: masks and filters can only be read and written in configuration mode

typedef struct mcp251x_message_id {
    uint8_t sidh;
    uint8_t sidl;
    uint8_t eid8;
    uint8_t eid0;
} mcp251x_message_id;


typedef struct mcp251x_frame_header {
    mcp251x_message_id id;
    uint8_t dlc;
} mcp251x_frame_header;


typedef struct mcp251x_message_buffer {
    mcp251x_frame_header header;
    uint8_t data[8];
} mcp251x_message_buffer;


// initializer for mcp251x_message_id
#define MCP251X_MESSAGE_ID(sid,eid,exide) {\
  .sidh=(uint8_t) ((sid) >> 3), \
  .sidl=(uint8_t) ((sid) & 3) | (exide != 0 ? 0x04 : 0x00) | ((eid) >> 16), \
  .eid8=(uint8_t) ( ((eid) >> 8) & 0xFF), \
  .eid0=(uint8_t) ((eid) & 0xFF)\
}

#endif