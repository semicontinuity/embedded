#ifndef ENCODER1_H
#define ENCODER1_H

#include <stdbool.h>
#include <stdint.h>

void encoder1__init(void);

void encoder1__debounce_timer__run(void);

void encoder1__run(void);

/**
 * Callback to be implemented to handle encoder rotation events.
 * @param delta determines the direction of rotation: 0x01 or 0xFF
 */
bool encoder1__handle_rotation_event(uint8_t delta);

#endif
