#ifndef __SENSORS_H
#define __SENSORS_H

#include <stdbool.h>


inline void sensors_a__init(void) {
    ENABLE_PULLUP(SENSORS_A0);
    ENABLE_PULLUP(SENSORS_A1);
    ENABLE_PULLUP(SENSORS_A2);
}

inline bool sensors_a__get(void) {
    // Sensor A2 is not used now
    return IS_1(SENSORS_A0) || IS_1(SENSORS_A1);
}


inline void sensors_b__init(void) {
    ENABLE_PULLUP(SENSORS_B0);
    ENABLE_PULLUP(SENSORS_B1);
    ENABLE_PULLUP(SENSORS_B2);
}

inline bool sensors_b__get(void) {
    // Sensor B2 is not used now
    return IS_1(SENSORS_B0) || IS_1(SENSORS_B1);
}

#endif