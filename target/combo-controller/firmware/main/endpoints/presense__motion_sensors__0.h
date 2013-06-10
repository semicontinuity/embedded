#ifndef __ENDPOINTS__PRESENSE__MOTION_SENSORS__0_H
#define __ENDPOINTS__PRESENSE__MOTION_SENSORS__0_H

#include <stdint.h>

void presense__motion_sensors__0__broadcast(void);

uint8_t* presense__motion_sensors__0__get_data(void);

void presense__motion_sensors__0__handle(const uint8_t* data);

#endif

