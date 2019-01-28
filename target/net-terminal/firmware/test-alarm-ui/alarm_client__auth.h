#ifndef __ALARM_CLIENT__AUTH_H
#define __ALARM_CLIENT__AUTH_H

#include "flags/alarm__state__changed.h"
#include <stdint.h>


struct alarm_client__auth__password {
    uint8_t length;
    uint8_t data[8];
};

extern struct alarm_client__auth__password alarm_client__auth__password;

INLINE void alarm_client__auth__password__on_invalidated(void);


inline void alarm_client__auth__password__set(const uint8_t length, const uint8_t* data) {
    alarm_client__auth__password.length = length;
    uint8_t* dst = alarm_client__auth__password.data;
    for (int8_t n = length; --n >= 0;) {
        *dst++ = *data++;
    }
    alarm__state__changed__set(1);
}


INLINE void alarm_client__auth__password__invalidate(void) {
    alarm_client__auth__password__on_invalidated();
}

#endif
    