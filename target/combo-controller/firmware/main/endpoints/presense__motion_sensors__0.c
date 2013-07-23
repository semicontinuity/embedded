#include "endpoints/presense__motion_sensors__0.h"

#include "flags/notifications_pending__presense__motion_sensors__0.h"
#include "flags/notifications_pending.h"

#include "motion_sensors_scanner.h"
#include "kernel.h"


void presense__motion_sensors__0__request_broadcast(void) {
    notifications_pending__presense__motion_sensors__0__set(1);
    notifications_pending__set(1);
}


void presense__motion_sensors__0__broadcast(void) {
    notifications_pending__presense__motion_sensors__0__set(0);
    mcp251x_message_id *id = &kernel__frame.header.id;
    UCAN_SET_DST(*id, UCAN_DST);
    UCAN_SET_VALUE_OBJID(*id, 0);
    UCAN_SET_PORT(*id, UCAN__PID__PRESENSE__MOTION_SENSORS);
    kernel__send_response(1, &motion_sensors_scanner__status.state);
}


/** From external sensors */
void presense__motion_sensors__0__handle(const uint8_t* data) {
    if (data[0]) alarm__sensor_active();
}
