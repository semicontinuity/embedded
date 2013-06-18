#include "endpoints/media__amplifier__0.h"

#include "flags/notifications_pending__media__amplifier__0.h"
#include "flags/notifications_pending.h"
#include "drivers/net/can/mcp251x/tx.h"


void media__amplifier__0__broadcast(void) {
    notifications_pending__media__amplifier__0__set(1);
    notifications_pending__set(1);
}


void media__amplifier__0__do_broadcast(void) {
    notifications_pending__media__amplifier__0__set(0);
    mcp2515__tx__txb1__send_report(UCAN__PID__MEDIA__AMPLIFIER, 1, &amplifier_relay__state);
}


/** From external sensors */
void media__amplifier__0__set_data(const uint8_t* data) {
    amplifier_relay__set(data[0]);
}
