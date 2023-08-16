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
//
//   * If 0 is written to the coil,
//     control signals will be frozen in the current state.
//
// - TARGET_POSITION
//   * 1: Opened
//   * 0: Closed
//
// - ERROR:
//   * 1: Actuator failed to reach target position (timeout)
//   * 0: Actuator has reached its target position (or action still in progress)
//   * Write 1 to abort any action in progress.
//     The actuator will be unpowered, possibly, in some half-open state.
// =============================================================================
#include <services/holding_registers.h>
#include "valve_controller__1.h"
#include "services/internal_coils.h"
#include "services/discrete_inputs.h"
#include "services/discrete_outputs.h"


uint8_t valve_controller__1__timeout;


void valve_controller__1__led__valve_open__set(bool on) {
    discrete_outputs__set(DISCRETE_OUTPUT__LED__VALVE__1__OPEN, on);
}

void valve_controller__1__led__valve_closed__set(bool on) {
    discrete_outputs__set(DISCRETE_OUTPUT__LED__VALVE__1__CLOSED, on);
}

bool valve_controller__1__button__open__get(void) {
    return discrete_inputs__get(DISCRETE_INPUT__BUTTON__VALVE_CONTROLLER__1__OPEN);
}

bool valve_controller__1__button__close__get(void) {
    return discrete_inputs__get(DISCRETE_INPUT__BUTTON__VALVE_CONTROLLER__1__CLOSE);
}


void valve_controller__1__active__set(bool value) {
    internal_coils__set(INTERNAL_COIL__VALVE_CONTROLLER__1__ACTIVE, value);
}

bool valve_controller__1__active__get(void) {
    return internal_coils__get(INTERNAL_COIL__VALVE_CONTROLLER__1__ACTIVE);
}


void valve_controller__1__target_position__set(bool opened) {
    internal_coils__set(INTERNAL_COIL__VALVE_CONTROLLER__1__TARGET_POSITION, opened);
}

bool valve_controller__1__target_position__get(void) {
    return internal_coils__get(INTERNAL_COIL__VALVE_CONTROLLER__1__TARGET_POSITION);
}


void valve_controller__1__failure__set(bool value) {
    internal_coil__8__set(value);
}

bool valve_controller__1__failure__get(void) {
    return internal_coil__8__get();
}


void valve_controller__1__actuator_power__set(bool on) {
    discrete_output__0__set(on);
}

void valve_controller__1__actuator_direction__set(bool opened) {
    discrete_output__1__set(opened);
}

bool valve_controller__1__actuator_direction__get(void) {
    return discrete_output__1__get();
}


bool valve_controller__1__limit_switch__valve_open__get(void) {
    return discrete_inputs__4__get();
}

bool valve_controller__1__limit_switch__valve_closed__get(void) {
    return discrete_inputs__5__get();
}


void valve_controller__1__activate(bool open_valve) {
    valve_controller__1__target_position__set(open_valve);
    valve_controller__1__active__set(true);
}


void valve_controller__1__deactivate(void) {
    valve_controller__1__actuator_power__set(false);
    valve_controller__1__actuator_direction__set(false);
    valve_controller__1__active__set(false);
    valve_controller__1__timeout = 0;
}


void valve_controller__1__close(void) {
    if (!valve_controller__1__limit_switch__valve_closed__get()) {
        valve_controller__1__activate(false);
    }
}

void valve_controller__1__open(void) {
    if (!valve_controller__1__limit_switch__valve_open__get()) {
        valve_controller__1__activate(true);
    }
}


bool valve_controller__1__is_runnable(void) {
    return valve_controller__1__active__get();
}

// Invoked on every tick of slow timer (every 250ms)
void valve_controller__1__run(void) {
    uint8_t timeout = valve_controller__1__timeout;
    if (timeout == 0) {
        // Timeout 0 means that the valve controller has been just activated.
        valve_controller__1__timeout = holding_registers__buffer__get(HOLDING_REGISTER__ADDRESS__VALVE_CONTROLLER__1__TIMEOUT_TICKS);
        valve_controller__1__actuator_direction__set(valve_controller__1__target_position__get());
        valve_controller__1__actuator_power__set(true);
        valve_controller__1__failure__set(false);
        valve_controller__1__led__valve_open__set(false);
        valve_controller__1__led__valve_closed__set(false);
    }
    else {
        --timeout;
        valve_controller__1__timeout = timeout;

        // Blink LED in "valve open" button if opening
        // Blink LED in "valve close" button if closing
        bool led_on = timeout & 0x01;
        if (valve_controller__1__actuator_direction__get())
            valve_controller__1__led__valve_open__set(led_on);
        else
            valve_controller__1__led__valve_closed__set(led_on);


        // Check the state of limit switches.
        // Assume, that on first invocation (in 250ms), the valve is in motion,
        // and both limit switches are open (the one, that was closed, is already open).
        bool finished;
        if (timeout == 0) {
            // Reached timeout, but limit switch has not been hit yet.
            valve_controller__1__failure__set(true);
            finished = false;
        } else {
            if (valve_controller__1__actuator_direction__get()) {
                // opening
                if (valve_controller__1__limit_switch__valve_closed__get()) valve_controller__1__failure__set(true);
                finished = valve_controller__1__limit_switch__valve_open__get();
            } else {
                // closing
                if (valve_controller__1__limit_switch__valve_open__get()) valve_controller__1__failure__set(true);
                finished = valve_controller__1__limit_switch__valve_closed__get();
            }
        }

        if (valve_controller__1__failure__get() || finished) {
            valve_controller__1__deactivate();
        }
    }
}


bool valve_controller__1__limit_switches_state_renderer__is_runnable(void) {
    return !valve_controller__1__is_runnable();
}

void valve_controller__1__limit_switches_state_renderer__run(void) {
    if (valve_controller__1__limit_switch__valve_open__get()) {
        valve_controller__1__led__valve_open__set(false);
    }
    if (valve_controller__1__limit_switch__valve_closed__get()) {
        valve_controller__1__led__valve_closed__set(false);
    }
}

// =============================================================================
// Button listeners
// =============================================================================

void valve_controller__1__button__open__changed(void) {
    if (valve_controller__1__button__open__get()) {
        // button pressed
        valve_controller__1__open();
    }
}

void valve_controller__1__button__close__changed(void) {
    if (valve_controller__1__button__close__get()) {
        // button pressed
        valve_controller__1__close();
    }
}
