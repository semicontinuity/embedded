#ifndef ENCODER3_H
#define ENCODER3_H

#include <stdbool.h>
#include <stdint.h>


void encoder3__init(void);

void encoder3__debounce_timer__run(void);

void encoder3__run(void);

/**
 * Callback to be implemented to handle encoder rotation events.
 * @param delta determines the direction of rotation: 0x01 or 0xFF
 */
bool encoder3__handle_rotation_event(uint8_t delta);


/**
 * Initialize debounce timer.
 */
void encoder3__debounce_timer__init(void);

/**
 * Start (or re-start) debounce timer.
 */
void encoder3__debounce_timer__start(void);

/**
 * @return true if debounce timer has started and timeout not yet elapsed (debouncing in progress)
 */
bool encoder3__debounce_timer__is_started(void) __attribute__((weak));


#endif
