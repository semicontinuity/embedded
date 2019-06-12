#ifndef ENCODER0__SWITCH_H
#define ENCODER0__SWITCH_H

#include <stdbool.h>
#include <stdint.h>


void encoder0__switch__init(void);

void encoder0__switch__run(void);

/**
 * Callback to be implemented to handle encoder switch events.
 * @param new_state determines the action: 0x00 if pressed, (1 << bit) if released
 */
bool encoder0__handle_switch_event(uint8_t encoder, uint8_t new_state, uint8_t bit);


/**
 * Initialize debounce timer.
 */
void encoder0__switch__debounce_timer__init(void);

/**
 * Start (or re-start) debounce timer.
 */
void encoder0__switch__debounce_timer__start(void);

/**
 * The callback, called when the debounce timer has expired.
 */
bool encoder0__switch__debounce_timer__is_started(void) __attribute__((weak));


#endif
