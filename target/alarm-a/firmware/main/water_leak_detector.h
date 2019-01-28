#ifndef __WATER_LEAK_DETECTOR_H
#define __WATER_LEAK_DETECTOR_H

#include "water_sensors.h"


void water_leak_detector__out__run(void);


inline static void water_leak_detector__run(void) {    
    static uint8_t water_leak_detected = 0;
    if ((water_leak_detected == 0) && (water_sensor_a__is_active() || water_sensor_b__is_active())) {
        water_leak_detected = 1;
        water_leak_detector__out__run();
    }
}

#endif

    