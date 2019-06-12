#ifndef ENCODER3__SWITCH_H
#define ENCODER3__SWITCH_H

#include <stdbool.h>
#include <stdint.h>


void encoder3__switch__init(void);

void encoder3__switch__run(void);


/**
 * Initialize debounce timer.
 */
void encoder3__switch__debounce_timer__init(void);

/**
 * Start (or re-start) debounce timer.
 */
void encoder3__switch__debounce_timer__start(void);

/**
 * The callback, called when the debounce timer has expired.
 */
bool encoder3__switch__debounce_timer__is_started(void) __attribute__((weak));


/**
 * Callback to be implemented to handle encoder switch events.
 * @param new_state determines the action: 0x00 if pressed, (1 << bit) if released
 */
bool encoder3__switch__handle_event(uint8_t new_state, uint8_t bit);


#endif
