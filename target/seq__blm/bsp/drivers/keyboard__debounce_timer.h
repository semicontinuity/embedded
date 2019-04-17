// =============================================================================
// Debounce timer for the keyboard.
// Invoke keyboard__debounce_timer__start() after any button event.
// When the timer expires, keyboard__debounce_timer__run() callback
// will be invoked and the timer stops until next call to start().
// =============================================================================

#ifndef __KEYBOARD__DEBOUNCE_TIMER_H
#define __KEYBOARD__DEBOUNCE_TIMER_H

/**
 * Initialize debounce timer.
 */
void keyboard__debounce_timer__init(void);

/**
 * Start (or re-start) debounce timer.
 */
void keyboard__debounce_timer__start(void);

/**
 * The callback called when the debounce timer has expired.
 */
void keyboard__debounce_timer__run(void);

#endif