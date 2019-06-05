// =============================================================================
// Debounce timer for the keyboard's port A
// =============================================================================

#ifndef __KEYBOARD__PORT_A__DEBOUNCE_TIMER_H
#define __KEYBOARD__PORT_A__DEBOUNCE_TIMER_H

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
void keyboard__port_a__debounce_timer__run(void);

#endif