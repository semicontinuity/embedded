#ifndef COMM_EVENTS_H
#define COMM_EVENTS_H

#include <stdint.h>
#include <stdbool.h>

// macros, not functions, because these values used to pass value to inline asm macro
#define COMM_EVENTS__ENCODER__ROTATION_EVENT(encoder, delta) (((encoder) << 5) | ((delta) & 0x1F))

// macros, not functions, because these values used to pass value to inline asm macro
#define COMM_EVENTS__ENCODER__ROTATION_EVENT_CLOCKWISE(encoder) (((encoder) << 2) | 0x01U)
#define COMM_EVENTS__ENCODER__ROTATION_EVENT_COUNTERCLOCKWISE(encoder) (((encoder) << 2) | 0x03U)

#define COMM_EVENTS__ENCODER__SWITCH_EVENT_DEPRESSED(encoder) (0x80 | ((encoder) << 2) | 0x01U)
#define COMM_EVENTS__ENCODER__SWITCH_EVENT_PRESSED(encoder) (0x80 | ((encoder) << 2) | 0x00U)

bool comm_events__queue__is_full(void);

void comm_events__queue__put(uint8_t event);

void comm_events__start(void);

#endif
