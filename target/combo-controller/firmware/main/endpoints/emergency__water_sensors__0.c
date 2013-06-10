#include "endpoints/emergency__water_sensors__0.h"

#include "flags/notifications_pending__emergency__water_sensors__0.h"
#include "flags/notifications_pending.h"

#include "water_leak_sensors_scanner.h"


void emergency__water_sensors__0__broadcast(void) {
    notifications_pending__emergency__water_sensors__0__set(1);
    notifications_pending__set(1);
}


uint8_t* emergency__water_sensors__0__get_data(void) {
    return &water_leak_sensors_scanner__status.state;
}
