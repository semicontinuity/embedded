#include "endpoints/emergency__water_actuators__0.h"

#include "flags/notifications_pending__emergency__water_actuators__0.h"
#include "flags/notifications_pending.h"
#include "drivers/out/water_valve.h"
#include "kernel.h"


void emergency__water_actuators__0__request_broadcast(void) {
    notifications_pending__emergency__water_actuators__0__set(1);
    notifications_pending__set(1);
}


void emergency__water_actuators__0__broadcast(void) {
    notifications_pending__emergency__water_actuators__0__set(1);
    mcp251x_message_id *id = &kernel__frame.header.id;
    UCAN_SET_DST(*id, UCAN_DST);
    UCAN_SET_VALUE_OBJID(*id, 0);
    UCAN_SET_PORT(*id, UCAN__PID__EMERGENCY__WATER_ACTUATORS);
    kernel__send_response(1, &water_valve__state);
}


void emergency__water_actuators__0__set_data(const uint8_t* data) {
    water_valve__set(data[0]);
}
