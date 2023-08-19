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
#include <services/basic_rtc.h>
#include "valve_controller__1.h"
#include "alert_controller.h"
#include "services/holding_registers.h"
#include "services/discrete_inputs.h"
#include "services/coils.h"


uint8_t valve_controller__1__timeout;

// Configuration
// -----------------------------------------------------------------------------

uint16_t valve_controller__1__timeout_ticks__get(void) {
    return holding_registers__buffer__get(HOLDING_REGISTER__ADDRESS__VALVE_CONTROLLER__1__TIMEOUT_TICKS);
}


// User interface I/O
// -----------------------------------------------------------------------------

void valve_controller__1__led__valve_open__set(bool on) {
    coils__set(DISCRETE_OUTPUT__LED__VALVE__1__OPEN, on);
}

void valve_controller__1__led__valve_closed__set(bool on) {
    coils__set(DISCRETE_OUTPUT__LED__VALVE__1__CLOSED, on);
}


bool valve_controller__1__button__open__get(void) {
    return discrete_inputs__get(DISCRETE_INPUT__BUTTON__VALVE_CONTROLLER__1__OPEN);
}

bool valve_controller__1__button__close__get(void) {
    return discrete_inputs__get(DISCRETE_INPUT__BUTTON__VALVE_CONTROLLER__1__CLOSE);
}


// Physical I/O
// -----------------------------------------------------------------------------

void valve_controller__1__actuator_power__set(bool on) {
    coils__set(DISCRETE_OUTPUT__VALVE_CONTROLLER__1__ACTUATOR_POWER, on);
}

void valve_controller__1__actuator_direction__set(bool open) {
    coils__set(DISCRETE_OUTPUT__VALVE_CONTROLLER__1__ACTUATOR_DIRECTION, open);
}

bool valve_controller__1__actuator_direction__get(void) {
    return coils__get(DISCRETE_OUTPUT__VALVE_CONTROLLER__1__ACTUATOR_DIRECTION);
}


bool valve_controller__1__limit_switch__valve_open__get(void) {
    return discrete_inputs__get(DISCRETE_INPUT__VALVE_CONTROLLER__1__LIMIT_SWITCH__VALVE_OPEN);
}

bool valve_controller__1__limit_switch__valve_closed__get(void) {
    return discrete_inputs__get(DISCRETE_INPUT__VALVE_CONTROLLER__1__LIMIT_SWITCH__VALVE_CLOSED);
}


// State
// -----------------------------------------------------------------------------

void valve_controller__1__target_position__set(bool opened) {
    coils__set(INTERNAL_COIL__VALVE_CONTROLLER__1__TARGET_POSITION, opened);
}

bool valve_controller__1__target_position__get(void) {
    return coils__get(INTERNAL_COIL__VALVE_CONTROLLER__1__TARGET_POSITION);
}


void valve_controller__1__requested__set(bool requested) {
    coils__set(INTERNAL_COIL__VALVE_CONTROLLER__1__REQUESTED, requested);
}

bool valve_controller__1__is_requested(void) {
    return coils__get(INTERNAL_COIL__VALVE_CONTROLLER__1__REQUESTED);
}


void valve_controller__1__running__set(bool requested) {
    coils__set(INTERNAL_COIL__VALVE_CONTROLLER__1__RUNNING, requested);
}

bool valve_controller__1__is_running(void) {
    return coils__get(INTERNAL_COIL__VALVE_CONTROLLER__1__RUNNING);
}


uint16_t valve_controller__1__idle_time_minutes__get(void) {
    return holding_registers__buffer__get(HOLDING_REGISTER__ADDRESS__VALVE_CONTROLLER__1__IDLE_TIME_MINUTES);
}

void valve_controller__1__idle_time_minutes__set(uint16_t value) {
    return holding_registers__buffer__set(HOLDING_REGISTER__ADDRESS__VALVE_CONTROLLER__1__IDLE_TIME_MINUTES, value);
}


// Logic
// -----------------------------------------------------------------------------

bool valve_controller__1__limit_switch__failure__get(void) {
    return !valve_controller__1__is_running() && !(valve_controller__1__limit_switch__valve_open__get() ^ valve_controller__1__limit_switch__valve_closed__get());
}

void valve_controller__1__activate(bool open_valve) {
    valve_controller__1__target_position__set(open_valve);
    valve_controller__1__requested__set(true);
}


void valve_controller__1__deactivate(void) {
    valve_controller__1__actuator_power__set(false);
    valve_controller__1__actuator_direction__set(false);
    valve_controller__1__running__set(false);
    valve_controller__1__requested__set(false);
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


void valve_controller__1__start_requested(void) {
    alerting__failure__valve_controller__1__push(false);
    valve_controller__1__led__valve_open__set(false);
    valve_controller__1__led__valve_closed__set(false);

    valve_controller__1__timeout = valve_controller__1__timeout_ticks__get();
    valve_controller__1__actuator_direction__set(valve_controller__1__target_position__get());
    valve_controller__1__actuator_power__set(true);
    valve_controller__1__running__set(true);
}

void valve_controller__1__run(void) {
    uint8_t timeout = valve_controller__1__timeout;

    // Check the state of limit switches.
    // Assume, that on first invocation (in 250ms), the valve is in motion,
    // and both limit switches are open (the one, that was closed, is already open).
    bool finished = false;
    bool error = false;
    if (timeout == 0) {
        // Reached timeout, but limit switch has not been hit yet.
        error = true;
    } else {
        --timeout;
        valve_controller__1__timeout = timeout;

        if (valve_controller__1__actuator_direction__get()) {
            // opening
            if (valve_controller__1__limit_switch__valve_closed__get()) {
                error = true;
            } else {
                finished = valve_controller__1__limit_switch__valve_open__get();
            }
        } else {
            // closing
            if (valve_controller__1__limit_switch__valve_open__get()) {
                error = true;
            } else {
                finished = valve_controller__1__limit_switch__valve_closed__get();
            }
        }
    }

    if (error) {
        alerting__failure__valve_controller__1__push(true);
    }
    if (finished || error) {
        valve_controller__1__deactivate();
    }
}

void valve_controller__1__stop_requested(void) {
    valve_controller__1__timeout = 0;
}


// =============================================================================
// State renderer
// =============================================================================

void valve_controller__1__limit_switches_state_renderer__run(void) {
    if (valve_controller__1__is_running()) {
        // use RTC seconds value, so that LEDs for both valves blink synchronously
        uint16_t seconds = basic_rtc__get_seconds();

        // Blink LED in "valve open" button if opening
        // Blink LED in "valve close" button if closing
        bool led_on = seconds & 0x01;
        if (valve_controller__1__actuator_direction__get())
            valve_controller__1__led__valve_open__set(led_on);
        else
            valve_controller__1__led__valve_closed__set(led_on);
    } else {
        if (valve_controller__1__limit_switch__valve_open__get()) {
            valve_controller__1__led__valve_open__set(false);
        }
        if (valve_controller__1__limit_switch__valve_closed__get()) {
            valve_controller__1__led__valve_closed__set(false);
        }
    }
}

// Must be invoked on every tick of slow timer (every 250 ms)
void valve_controller__1__on_slow_timer_tick(void) {
    if (valve_controller__1__is_running()) {
        if (!valve_controller__1__is_requested()) {
            valve_controller__1__stop_requested();
        }
        valve_controller__1__run();
        valve_controller__1__idle_time_minutes__set(0);
    } else {
        if (valve_controller__1__is_requested()) {
            valve_controller__1__start_requested();
        }
    }

    valve_controller__1__limit_switches_state_renderer__run();
}

// Must be invoked on every tick of the minute timer
void valve_controller__1__on_minutes_timer_tick(void) {
    valve_controller__1__idle_time_minutes__set(valve_controller__1__idle_time_minutes__get() + 1);
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
