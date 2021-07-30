// =============================================================================
// Debounce timer A
// =============================================================================

#ifndef __KEYBOARD__DEBOUNCE_TIMER__A_H
#define __KEYBOARD__DEBOUNCE_TIMER__A_H

#include <stdbool.h>

/**
 * Initialize debounce timer.
 */
void keyboard__debounce_timer__a__init(void) __attribute__((weak));

/**
 * Start (or re-start) debounce timer.
 */
void keyboard__debounce_timer__a__start(void);

/**
 * The callback, called when the debounce timer has expired.
 */
bool keyboard__debounce_timer__a__is_started(void) __attribute__((weak));

/**
 * The callback, called when the debounce timer has expired.
 */
void keyboard__debounce_timer__a__run(void) __attribute__((weak));

#endif