// =============================================================================
// Master Failure indicator
//
// Master Failure LED (in button) is ON, when any of failure flags is ON.
// Pressing the button resets all failure flags, and the LED becomes OFF.
// =============================================================================
#include "contactor_control.h"
#include "valve_controller__1.h"
#include "water_leak_sensors_controller.h"

#include "services/discrete_outputs.h"
#include "services/discrete_inputs.h"


void failure_indicator__led__set(bool value) {
    discrete_outputs__set(DISCRETE_OUTPUT__FAILURE_INDICATOR__LED, value);
}

bool failure_indicator__button__get(void) {
    return discrete_inputs__get(DISCRETE_INPUT__FAILURE_INDICATOR__BUTTON);
}

void failure_indicator__run(void) {
    failure_indicator__led__set(
            contactor_control__failure__get()
            || valve_controller__1__failure__get()
            || water_leak_sensor_controller__failure__get()
    );
}

// =============================================================================
// Button listener
// =============================================================================

void failure_indicator__button__changed() {
    if (failure_indicator__button__get()) {
        // if pressed
        contactor_control__failure__set(false);
        valve_controller__1__failure__set(false);
        water_leak_sensor_controller__failure__set(false);
    }
}
