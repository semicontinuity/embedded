// =============================================================================
// Debounce timer D
// =============================================================================

#ifndef __KEYBOARD__DEBOUNCE_TIMER__D_H
#define __KEYBOARD__DEBOUNCE_TIMER__D_H

#include <stdbool.h>

/**
 * Initialize debounce timer.
 */
void keyboard__debounce_timer__d__init(void) __attribute__((weak));

/**
 * Start (or re-start) debounce timer.
 */
void keyboard__debounce_timer__d__start(void);

/**
 * The callback, called when the debounce timer has expired.
 */
bool keyboard__debounce_timer__d__is_started(void) __attribute__((weak));

/**
 * The callback, called when the debounce timer has expired.
 */
void keyboard__debounce_timer__d__run(void) __attribute__((weak));

#endif