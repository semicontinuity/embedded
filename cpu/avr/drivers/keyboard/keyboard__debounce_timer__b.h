// =============================================================================
// Debounce timer B
// =============================================================================

#ifndef __KEYBOARD__DEBOUNCE_TIMER__B_H
#define __KEYBOARD__DEBOUNCE_TIMER__B_H

#include <stdbool.h>

/**
 * Initialize debounce timer.
 */
void keyboard__debounce_timer__b__init(void) __attribute__((weak));

/**
 * Start (or re-start) debounce timer.
 */
void keyboard__debounce_timer__b__start(void);

/**
 * The callback, called when the debounce timer has expired.
 */
bool keyboard__debounce_timer__b__is_started(void) __attribute__((weak));

/**
 * The callback, called when the debounce timer has expired.
 */
void keyboard__debounce_timer__b__run(void) __attribute__((weak));

#endif