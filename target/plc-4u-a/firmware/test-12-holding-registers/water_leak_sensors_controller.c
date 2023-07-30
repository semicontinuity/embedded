// =============================================================================
// Water leak sensor controller (digital).
//
// When any of the water leak sensors is ON,
// instructs water valve controllers to close valves.
// * Turns on Failure Indicator and Buzzer (for 1 minute)
// =============================================================================
#include "water_leak_sensors_controller.h"
#include "services/internal_coils.h"
#include "services/discrete_inputs.h"
#include "valve_controller__1.h"


bool water_leak_sensor_controller__sensor__a__get(void) {
    return discrete_inputs__0__get();
}

bool water_leak_sensor_controller__sensor__b__get(void) {
    return discrete_inputs__1__get();
}

bool water_leak_sensor_controller__sensor__c__get(void) {
    return discrete_inputs__2__get();
}

bool water_leak_sensor_controller__sensor__d__get(void) {
    return discrete_inputs__3__get();
}


void water_leak_sensor_controller__failure__set(bool value) {
    internal_coil__b__set(value);
}

bool water_leak_sensor_controller__failure__get(void) {
    return internal_coil__b__get();
}

bool water_leak_sensor_controller__any_sensor_is_active(void) {
    return water_leak_sensor_controller__sensor__a__get()
    || water_leak_sensor_controller__sensor__b__get()
    || water_leak_sensor_controller__sensor__c__get()
    || water_leak_sensor_controller__sensor__d__get();
}


bool water_leak_sensor_controller__is_runnable(void) {
    return !water_leak_sensor_controller__failure__get();
}

void water_leak_sensor_controller__run(void) {
    if (water_leak_sensor_controller__any_sensor_is_active()) {
        water_leak_sensor_controller__failure__set(true);
        valve_controller__1__close();
    }
}
