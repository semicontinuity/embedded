#ifndef __ALARM_CLIENT__AUTH_H
#define __ALARM_CLIENT__AUTH_H

#include <stdint.h>


struct alarm_client__auth__password {
    uint8_t length;
    uint8_t data[8];
};

extern struct alarm_client__auth__password alarm_client__auth__password;


inline static void alarm_client__auth__init(void) {
    // TODO request
}

inline void alarm_client__auth__password__set(const uint8_t length, const uint8_t* data) {
    alarm_client__auth__password.length = length;
    uint8_t* dst = alarm_client__auth__password.data;
    for (int8_t n = length; --n >= 0;) {
        *dst++ = *data++;
    }
}

#endif
    