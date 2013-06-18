#ifndef __ENDPOINTS__PRESENSE__MOTION_SENSORS__0_H
#define __ENDPOINTS__PRESENSE__MOTION_SENSORS__0_H

#include <stdint.h>

void presense__motion_sensors__0__broadcast(void);

void presense__motion_sensors__0__do_broadcast(void);

void presense__motion_sensors__0__handle(const uint8_t* data);

#endif

