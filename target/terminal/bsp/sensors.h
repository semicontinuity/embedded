#ifndef __SENSORS_H
#define __SENSORS_H

#include "cpu/avr/gpio.h"

#define sensors_read()    (PORT_VALUE(SENSORS) & (_BV(SENSOR0__PIN)|_BV(SENSOR1__PIN)|_BV(SENSOR2__PIN)|_BV(SENSOR3__PIN)))

// Configure PC2-PC5 for input
// 1. (do nothing with DDRC - input by default)
// 2. activate internal pull ups
inline void sensors__init(void) {
    ENABLE_PULLUP(SENSOR0);
    ENABLE_PULLUP(SENSOR1);
    ENABLE_PULLUP(SENSOR2);
    ENABLE_PULLUP(SENSOR3);
}

#endif
