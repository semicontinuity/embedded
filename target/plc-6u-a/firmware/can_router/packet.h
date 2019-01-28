#ifndef __PACKET_H
#define __PACKET_H

#define PACKET_LENGTH	(13)	// (sizeof(mcp251x_message_buffer)) - hardcoded to be usable in inline asm
#define PACKET_Q_STRIDE	(16)	// Rounded to next power of 2 to make circular queue efficient


#include "cpu/avr/asm.h"

/**
 * Copy the packet header (5 bytes)
 * @param register Y - source pointer
 * @param register Z - destination pointer
 */
inline static void packet__copy_header(void) {
    YPLUS_TO_ZPLUS();
    YPLUS_TO_ZPLUS();
    YPLUS_TO_ZPLUS();
    YPLUS_TO_ZPLUS();
    YPLUS_TO_ZPLUS();
}

/**
 * Copy the packet payload (8 bytes)
 * @param register Y - source pointer
 * @param register Z - destination pointer
 */
inline static void packet__copy_payload(void) {
    YPLUS_TO_ZPLUS();
    YPLUS_TO_ZPLUS();
    YPLUS_TO_ZPLUS();
    YPLUS_TO_ZPLUS();
    YPLUS_TO_ZPLUS();
    YPLUS_TO_ZPLUS();
    YPLUS_TO_ZPLUS();
    YPLUS_TO_ZPLUS();
}

/**
 * Copy the packet (5+8 bytes)
 * @param register Y - source pointer
 * @param register Z - destination pointer
 */
inline static void packet__copy(void) {
    packet__copy_header();
    packet__copy_payload();
}


#endif // __PACKET_H