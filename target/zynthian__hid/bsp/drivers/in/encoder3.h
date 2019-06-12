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

#endif
