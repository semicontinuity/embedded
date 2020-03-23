#ifndef ENCODER0_H
#define ENCODER0_H

#include <stdbool.h>
#include <stdint.h>

void encoder0__init(void);

void encoder0__debounce_timer__run(void);

void encoder0__run(void);

/**
 * Callback to be implemented to handle encoder rotation events.
 * @param delta determines the direction of rotation: 0x01 or 0xFF
 */
bool encoder0__handle_rotation_event(uint8_t delta);

#endif
