#ifndef __PACKET_H
#define __PACKET_H

#define PACKET_LENGTH	(13)	// (sizeof(mcp251x_message_buffer)) - hardcoded to be usable in inline asm
#define PACKET_Q_STRIDE	(16)	// Rounded to next power of 2 to make circular queue efficient

#endif // __PACKET_H