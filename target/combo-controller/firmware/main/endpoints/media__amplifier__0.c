#include "endpoints/media__amplifier__0.h"

#include "flags/notifications_pending__media__amplifier__0.h"
#include "flags/notifications_pending.h"
#include "kernel.h"


void media__amplifier__0__request_broadcast(void) {
    notifications_pending__media__amplifier__0__set(1);
    notifications_pending__set(1);
}


void media__amplifier__0__broadcast(void) {
    notifications_pending__media__amplifier__0__set(0);
    mcp251x_message_id *id = &kernel__frame.header.id;
    UCAN_SET_DST(*id, UCAN_DST);
    UCAN_SET_VALUE_OBJID(*id, 0);
    UCAN_SET_PORT(*id, UCAN__PID__MEDIA__AMPLIFIER);
    kernel__send_response(1, &amplifier_relay__state);
}


/** From external sensors */
void media__amplifier__0__set_data(const uint8_t* data) {
    amplifier_relay__set(data[0]);
}
