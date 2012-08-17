#ifndef __IN_SENSOR_LINE__H
#define __IN_SENSOR_LINE__H

#include "cpu/avr/gpio.h"
#include <stdbool.h>


static inline void sensor_line__init(void) {}


static inline bool sensor_line__is_active(void) {
    return IS_0(SENSOR_LINE);
}

static inline void sensor_line__on_active(void);

static inline void sensor_line__run(void) {    
    if (sensor_line__is_active()) sensor_line__on_active(); // makes sense to poll, to filter out noise
}

#endif