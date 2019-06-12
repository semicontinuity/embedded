#ifndef ENCODER2_H
#define ENCODER2_H

#include <stdbool.h>
#include <stdint.h>


void encoder2__init(void);

void encoder2__run(void);


/**
 * Initialize debounce timer.
 */
void encoder2__debounce_timer__init(void);

/**
 * Start (or re-start) debounce timer.
 */
void encoder2__debounce_timer__start(void);

/**
 * @return true if debounce timer has started and timeout not yet elapsed (debouncing in progress)
 */
bool encoder2__debounce_timer__is_started(void) __attribute__((weak));

void encoder2__debounce_timer__run(void) __attribute__((weak));


/**
 * Callback to be implemented to handle encoder rotation events.
 * @param delta determines the direction of rotation: 0x01 or 0xFF
 */
bool encoder2__handle_event(uint8_t delta);


#endif
