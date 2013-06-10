#include "endpoints/presense__motion_sensors__0.h"

#include "flags/notifications_pending__presense__motion_sensors__0.h"
#include "flags/notifications_pending.h"

#include "motion_sensors_scanner.h"


void presense__motion_sensors__0__broadcast(void) {
    notifications_pending__presense__motion_sensors__0__set(1);
    notifications_pending__set(1);
}


uint8_t* presense__motion_sensors__0__get_data(void) {
    return &motion_sensors_scanner__status.state;
}


/** From external sensors */
void presense__motion_sensors__0__handle(const uint8_t* data) {
    if (data[0]) alarm__sensor_active();
}
