// =============================================================================
// Valve controller: controls valve actuator. (2 channels)
//
// There are 3 internal coils, associated with each valve control channel:
// - ACTIVE
//   Write 1 to request to open or close valve.
//   The actuator will be powered and will open or close the valve.
//   Once the movement finishes (limit switch engaged or timeout expires),
//   the coil value will be changed to 0.
//   * If the coil value reads as 1, there is an actuator action in progress.
//   * If the coil value reads as 0, there is no actuator action in progress.
//   * Write 0 to abort any action in progress.
//     The actuator will be unpowered, possibly, in some half-open state.
//
// - TARGET_POSITION
//   * 1: Opened
//   * 0: Closed
//
// - ERROR:
//   * 1: Actuator failed to reach target position (timeout)
//   * 0: Actuator has reached its target position (or action still in progress)
// =============================================================================
#include "valve_controller.h"
#include "services/internal_coils.h"
#include "services/discrete_outputs.h"


uint8_t valve_controller__1__timeout;


void valve_controller__1__active__set(bool value) {
    internal_coil__0__set(value);
}

bool valve_controller__1__active__get(void) {
    return internal_coil__0__get();
}


void valve_controller__1__target_position__set(bool opened) {
    internal_coil__1__set(opened);
}

bool valve_controller__1__target_position__get(void) {
    return internal_coil__1__get();
}


void valve_controller__1__error__set(bool value) {
    internal_coil__2__set(value);
}

bool valve_controller__1__error__get(void) {
    return internal_coil__2__get();
}


void valve_controller__1__actuator_power__set(bool on) {
    discrete_output__0__set(on);
}

void valve_controller__1__actuator_direction__set(bool opened) {
    discrete_output__1__set(opened);
}


void valve_controller__1__activate(bool open_valve) {
    valve_controller__1__target_position__set(open_valve);
    valve_controller__1__active__set(true);
}


void valve_controller__1__deactivate(bool error) {
    valve_controller__1__error__set(error);
    valve_controller__1__actuator_power__set(false);
    valve_controller__1__actuator_direction__set(false);
    valve_controller__1__active__set(false);
}


bool valve_controller__1__is_runnable(void) {
    return valve_controller__1__active__get();
}

void valve_controller__1__run(void) {
    uint8_t timeout = valve_controller__1__timeout;
    if (timeout == 0) {
        // Timeout 0 means that the valve controller has been just activated.
        valve_controller__1__timeout = 5*4;
        valve_controller__1__actuator_direction__set(valve_controller__1__target_position__get());
        valve_controller__1__actuator_power__set(true);
        valve_controller__1__error__set(false);
    }
    else {
        --timeout;
        if (timeout == 0) {
            // Timeout expired
            valve_controller__1__deactivate(true);
        }
        valve_controller__1__timeout = timeout;
    }
}
