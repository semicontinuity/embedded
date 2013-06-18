#include "endpoints/presense__motion_sensors__0.h"

#include "flags/notifications_pending__presense__motion_sensors__0.h"
#include "flags/notifications_pending.h"

#include "motion_sensors_scanner.h"


void presense__motion_sensors__0__broadcast(void) {
    notifications_pending__presense__motion_sensors__0__set(1);
    notifications_pending__set(1);
}


void presense__motion_sensors__0__do_broadcast(void) {
    notifications_pending__presense__motion_sensors__0__set(0);
    mcp2515__tx__txb1__send_report(UCAN__PID__PRESENSE__MOTION_SENSORS, 1, &motion_sensors_scanner__status.state);
}


/** From external sensors */
void presense__motion_sensors__0__handle(const uint8_t* data) {
    if (data[0]) alarm__sensor_active();
}
