#include "endpoints/emergency__water_sensors__0.h"

#include "flags/notifications_pending__emergency__water_sensors__0.h"
#include "flags/notifications_pending.h"

#include "water_leak_sensors_scanner.h"


void emergency__water_sensors__0__broadcast(void) {
    notifications_pending__emergency__water_sensors__0__set(1);
    notifications_pending__set(1);
}


void emergency__water_sensors__0__do_broadcast(void) {
    notifications_pending__emergency__water_sensors__0__set(0);
    mcp2515__tx__txb1__send_report(UCAN__PID__EMERGENCY__WATER_SENSORS, 1, &water_leak_sensors_scanner__status.state);
}
