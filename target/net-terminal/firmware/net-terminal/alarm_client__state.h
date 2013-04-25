#ifndef __ALARM_CLIENT__STATE_H
#define __ALARM_CLIENT__STATE_H

#include <stdint.h>

extern uint8_t alarm_client__state;
extern uint8_t alarm_client__new_state;

INLINE void alarm_client__state__on_changed(void);

INLINE void alarm_client__new_state__on_changed(void);


INLINE void alarm_client__state__set(const uint8_t state) {
    alarm_client__state = state;
}

INLINE void alarm_client__server_state__set(const uint8_t state) {
    alarm_client__new_state = state;
    alarm_client__new_state__on_changed();
}

#endif