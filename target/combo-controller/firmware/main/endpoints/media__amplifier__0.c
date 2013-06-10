#include "endpoints/media__amplifier__0.h"

#include "flags/notifications_pending__media__amplifier__0.h"
#include "flags/notifications_pending.h"


void media__amplifier__0__broadcast(void) {
    notifications_pending__media__amplifier__0__set(1);
    notifications_pending__set(1);
}


uint8_t* media__amplifier__0__get_data(void) {
    return &amplifier_relay__state;
}


/** From external sensors */
void media__amplifier__0__set_data(const uint8_t* data) {
    amplifier_relay__set(data[0]);
}
