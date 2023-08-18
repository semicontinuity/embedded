#ifndef WATER_LEAK_SENSOR_CONTROLLER_H
#define WATER_LEAK_SENSOR_CONTROLLER_H

#include <stdbool.h>


bool water_leak_sensor_controller__alarm__a__get(void);
bool water_leak_sensor_controller__alarm__b__get(void);
bool water_leak_sensor_controller__alarm__c__get(void);
bool water_leak_sensor_controller__alarm__d__get(void);

bool water_leak_sensor_controller__sensor__a__had_leak__get(void);
bool water_leak_sensor_controller__sensor__b__had_leak__get(void);
bool water_leak_sensor_controller__sensor__c__had_leak__get(void);
bool water_leak_sensor_controller__sensor__d__had_leak__get(void);

void water_leak_sensor_controller__run(void);


#endif