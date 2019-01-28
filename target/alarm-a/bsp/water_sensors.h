#ifndef __WATER_SENSORS_H
#define __WATER_SENSORS_H

#include "cpu/avr/gpio.h"
#include <stdbool.h>


static inline void water_sensor_a__init(void) {}


static inline bool water_sensor_a__is_active(void) {
    return IS_0(WATER_SENSOR_A);
}



static inline void water_sensor_b__init(void) {}


static inline bool water_sensor_b__is_active(void) {
    return IS_0(WATER_SENSOR_B);
}


#endif