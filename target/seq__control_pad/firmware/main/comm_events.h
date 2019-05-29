#ifndef COMM_EVENTS_H
#define COMM_EVENTS_H

#include <stdint.h>
#include <stdbool.h>

bool comm_events__queue__is_full(void);

void comm_events__queue__put(uint8_t event);

void comm_events__start(void);

inline bool comm_events__encoder_rotation_event_clockwise(const uint8_t encoder) {
    return ((uint8_t)(encoder << 2U) | 0x01U);
}

inline bool comm_events__encoder_rotation_event_counterclockwise(const uint8_t encoder) {
    return ((uint8_t)(encoder << 2U) | 0x03U);
}

#endif
