#ifndef WATER_LEAK_SENSOR_CONTROLLER_H
#define WATER_LEAK_SENSOR_CONTROLLER_H

#include <stdbool.h>


void water_leak_sensor_controller__failure__set(bool value);
bool water_leak_sensor_controller__failure__get(void);

bool water_leak_sensor_controller__is_runnable(void);
void water_leak_sensor_controller__run(void);


#endif