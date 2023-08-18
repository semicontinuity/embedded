// =============================================================================
// Alarm controller.
// Manages Alert LED and Alamr Buzzer.
//
// Maintains multiple alarm and failure flags on behalf of other controllers.
// - Some controllers may set failure flags
//   to indicate the failure of a long-running operation (PUSH mode).
//   Alert is triggered, when the flag is set to True,
//   and its previous value was False.
// - Some controllers may compute alarm or failure flags on-demand (PULL mode).
//   In this case, if a controller reports True alert condition,
//   and the corresponding flag is False, the alert is triggered.
//
// - If any of the alarm or failure flags are set,
//   Master Alarm LED (in button) is lighted.
//
// - If alert is triggered, buzzer is requested.
//
// - Pressing the button attempts to reset alarm and failure flags:
//   - Flags, set using PUSH mode, are reset.
//   - For flags, set using PULL mode, a query is issued
//     to the corresponding controller for the current state of alert,
//     and the flag is set to the current state of alert.
//     Thus, is the flag is True, and the current alert is False,
//     the flag is reset.
//     If the current alert is True, the flag remains True.
//     The buzzer will not be triggered, even though alert is active.
// =============================================================================
#include "valve_controller__1.h"
#include "water_leak_sensors_controller.h"

#include "services/coils.h"
#include "services/discrete_inputs.h"
#include "buzzer_controller.h"


// Failure flags
// -----------------------------------------------------------------------------

void alerting__failure__contactor_controller__set(bool value) {
    if (value && !coils__get(INTERNAL_COIL__CONTACTOR_CONTROL__FAILURE)) {
        buzzer_controller__requested__set(true);
    }
    coils__set(INTERNAL_COIL__CONTACTOR_CONTROL__FAILURE, value);
}

bool alerting__failure__contactor_controller__get(void) {
    return coils__get(INTERNAL_COIL__CONTACTOR_CONTROL__FAILURE);
}


// Physical I/O
// -----------------------------------------------------------------------------

void alarm_controller__led__set(bool value) {
    coils__set(DISCRETE_OUTPUT__LED__ALARM, value);
}

bool alarm_controller__button__get(void) {
    return discrete_inputs__get(DISCRETE_INPUT__BUTTON__ALARM);
}


// Logic
// -----------------------------------------------------------------------------

/**
 * LED is on, when any
 */
void alarm_controller__run(void) {
    alarm_controller__led__set(
            alerting__failure__contactor_controller__get()
            || valve_controller__1__failure__get()
            || water_leak_sensor_controller__alarm__get()
    );
}

// =============================================================================
// Button listener
// =============================================================================

/**
 * TODO:
 * Should memorize the combination of alarm conditions at the time of button press.
 * If conditions are the same, do not light up LED and trigger buzzer.
 */
void alarm_controller__button__changed() {
    if (alarm_controller__button__get()) { // if pressed
        alerting__failure__contactor_controller__set(false);
        valve_controller__1__failure__set(false);
        water_leak_sensor_controller__alarm__reset();
    }
}
