#include "endpoints/emergency__water_actuators__0.h"

#include "flags/notifications_pending__emergency__water_actuators__0.h"
#include "flags/notifications_pending.h"
#include "drivers/out/water_valve.h"


void emergency__water_actuators__0__broadcast(void) {
    notifications_pending__emergency__water_actuators__0__set(1);
    notifications_pending__set(1);
}


uint8_t* emergency__water_actuators__0__get_data(void) {
    return &water_valve__state;
}


void emergency__water_actuators__0__set_data(const uint8_t* data) {
    water_valve__set(data[0]);
}
