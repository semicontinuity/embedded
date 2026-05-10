#include "endpoints/emergency__water_sensors__0.h"

#include "flags/notifications_pending__emergency__water_sensors__0.h"
#include "flags/notifications_pending.h"

#include "water_leak_sensors_scanner.h"
#include "kernel.h"


void emergency__water_sensors__0__request_broadcast(void) {
    notifications_pending__emergency__water_sensors__0__set(1);
    notifications_pending__set(1);
}


void emergency__water_sensors__0__broadcast(void) {
    notifications_pending__emergency__water_sensors__0__set(0);
    mcp251x_message_id *id = &kernel__frame.header.id;
    UCAN_SET_DST(*id, UCAN_DST);
    UCAN_SET_VALUE_OBJID(*id, 1);
    UCAN_SET_PORT(*id, UCAN__PID__EMERGENCY__WATER_SENSORS);
    kernel__send_response(1, &water_leak_sensors_scanner__status.state);
}
