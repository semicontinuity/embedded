#ifndef ENCODER1__SWITCH_H
#define ENCODER1__SWITCH_H

#include <stdbool.h>
#include <stdint.h>


void encoder1__switch__init(void);

void encoder1__switch__run(void);


/**
 * Initialize debounce timer.
 */
void encoder1__switch__debounce_timer__init(void);

/**
 * Start (or re-start) debounce timer.
 */
void encoder1__switch__debounce_timer__start(void);

/**
 * The callback, called when the debounce timer has expired.
 */
bool encoder1__switch__debounce_timer__is_started(void) __attribute__((weak));


/**
 * Callback to be implemented to handle encoder switch events.
 * @param new_state determines the action: 0x00 if pressed, (1 << bit) if released
 */
bool encoder1__switch__handle_event(uint8_t new_state, uint8_t bit);


#endif
