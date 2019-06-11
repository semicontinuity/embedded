// =============================================================================
// Debounce timer for the keyboard's port A
// =============================================================================

#ifndef __KEYBOARD__PORT_A__DEBOUNCE_TIMER_H
#define __KEYBOARD__PORT_A__DEBOUNCE_TIMER_H

#include <stdbool.h>

/**
 * Initialize debounce timer.
 */
void keyboard__port_a__debounce_timer__init(void);

/**
 * Start (or re-start) debounce timer.
 */
void keyboard__port_a__debounce_timer__start(void);

/**
 * The callback, called when the debounce timer has expired.
 */
bool keyboard__port_a__debounce_timer__is_started(void) __attribute__((weak));

/**
 * The callback, called when the debounce timer has expired.
 */
void keyboard__port_a__debounce_timer__run(void) __attribute__((weak));

#endif