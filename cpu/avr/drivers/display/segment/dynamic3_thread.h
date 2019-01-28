// =============================================================================
// The driver for the 3-digit 7-segment multiplexed common-anode display.
// Implements dynamic lighting.
//
// Usage:
//
// To initialize, call display_thread__init().
// Then, call display_thread__run() periodically, e.g. 250 times per second.
//
// Put the data to be displayed into display_thread__segments.
//
// Blinking support:
//
// To turn on blinking, call display_thread__blink__on().
// To turn off blinking, call display_thread__blink__off().
// Call display_thread__phase_on() and display_thread__phase_off() periodically.
// =============================================================================

#ifndef __CPU__AVR__DRIVERS__DISPLAY__SEGMENT__DYNAMIC3_THREAD_H
#define __CPU__AVR__DRIVERS__DISPLAY__SEGMENT__DYNAMIC3_THREAD_H

#include <stdint.h>

/**
 * The data to be displayed.
 * These are the raw segment data to be writen to the segments port.
 */
extern volatile uint8_t display_thread__segments[3];


INLINE void display_thread__init(void);
INLINE void display_thread__run(void);
INLINE void display_thread__phase_on(void);
INLINE void display_thread__phase_off(void);
INLINE void display_thread__blink__on(void);
INLINE void display_thread__blink__off(void);

#endif