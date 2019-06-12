#ifndef ENCODER2_H
#define ENCODER2_H

#include <stdbool.h>
#include <stdint.h>

void encoder2__init(void);

void encoder2__debounce_timer__run(void);

void encoder2__run(void);

/**
 * Callback to be implemented to handle encoder rotation events.
 * @param delta determines the direction of rotation: 0x01 or 0xFF
 */
bool encoder2__handle_rotation_event(uint8_t delta);

#endif
