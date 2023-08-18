// =============================================================================
// Alert controller.
// Manages Alert LED and Alarm Buzzer.
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
//
// Alert handling
//
// - When any of the water leak sensors is becomes ON,
//   instructs water valve controllers to close valves (if enabled).
// =============================================================================
#include <services/holding_registers.h>
#include "alert_controller.h"
#include "valve_controller__1.h"
#include "water_leak_sensors_controller.h"

#include "services/coils.h"
#include "services/discrete_inputs.h"
#include "buzzer_controller.h"


// Configuration
// -----------------------------------------------------------------------------

bool alerting__buzzer__enabled(void) {
    return holding_registers__buffer__get(HOLDING_REGISTER__ADDRESS__BUZZER__ENABLED);
}

bool alerting__closure_of_water_valves_on_leak__enabled(void) {
    return holding_registers__buffer__get(HOLDING_REGISTER__ADDRESS__CLOSURE_OF_WATER_VALVES_ON_LEAK__ENABLED);
}


// Alert handlers
// -----------------------------------------------------------------------------

void alerting__request_buzzer(void) {
    if (alerting__buzzer__enabled()) {
        buzzer_controller__requested__set(true);
    }
}

void alerting__handle_water_leak_sensor_alert(void) {
    alerting__request_buzzer();

    if (alerting__closure_of_water_valves_on_leak__enabled()) {
        valve_controller__1__close();
    }
}

// Failure flags
// -----------------------------------------------------------------------------

bool alerting__failure__contactor_controller__get(void) {
    return coils__get(INTERNAL_COIL__CONTACTOR_CONTROL__FAILURE);
}

void alerting__failure__contactor_controller__set(bool value) {
    coils__set(INTERNAL_COIL__CONTACTOR_CONTROL__FAILURE, value);
}

void alerting__failure__contactor_controller__push(bool value) {
    if (value && !alerting__failure__contactor_controller__get()) {
        alerting__request_buzzer();
    }
    alerting__failure__contactor_controller__set(value);
}


bool alerting__failure__valve_controller__1__get(void) {
    return coils__get(INTERNAL_COIL__VALVE_CONTROLLER__1__FAILURE);
}

void alerting__failure__valve_controller__1__set(bool value) {
    coils__set(INTERNAL_COIL__VALVE_CONTROLLER__1__FAILURE, value);
}

void alerting__failure__valve_controller__1__push(bool value) {
    if (value && !alerting__failure__contactor_controller__get()) {
        alerting__request_buzzer();
    }
    alerting__failure__valve_controller__1__set(value);
}


// Alarm flags
// -----------------------------------------------------------------------------

bool alerting__alarm__water_leak_sensor_controller__a__get(void) {
    return coils__get(INTERNAL_COIL__ALARM__WATER_LEAK_SENSOR__A);
}

void alerting__alarm__water_leak_sensor_controller__a__set(bool value) {
    coils__set(INTERNAL_COIL__ALARM__WATER_LEAK_SENSOR__A, value);
}

void alerting__alarm__water_leak_sensor_controller__a__push(bool value) {
    if (value && !alerting__alarm__water_leak_sensor_controller__a__get()) {
        alerting__handle_water_leak_sensor_alert();
    }
    alerting__alarm__water_leak_sensor_controller__a__set(value);
}


bool alerting__alarm__water_leak_sensor_controller__b__get(void) {
    return coils__get(INTERNAL_COIL__ALARM__WATER_LEAK_SENSOR__B);
}

void alerting__alarm__water_leak_sensor_controller__b__set(bool value) {
    coils__set(INTERNAL_COIL__ALARM__WATER_LEAK_SENSOR__B, value);
}

void alerting__alarm__water_leak_sensor_controller__b__push(bool value) {
    if (value && !alerting__alarm__water_leak_sensor_controller__a__get()) {
        alerting__handle_water_leak_sensor_alert();
    }
    alerting__alarm__water_leak_sensor_controller__b__set(value);
}


bool alerting__alarm__water_leak_sensor_controller__c__get(void) {
    return coils__get(INTERNAL_COIL__ALARM__WATER_LEAK_SENSOR__C);
}

void alerting__alarm__water_leak_sensor_controller__c__set(bool value) {
    coils__set(INTERNAL_COIL__ALARM__WATER_LEAK_SENSOR__C, value);
}

void alerting__alarm__water_leak_sensor_controller__c__push(bool value) {
    if (value && !alerting__alarm__water_leak_sensor_controller__a__get()) {
        alerting__handle_water_leak_sensor_alert();
    }
    alerting__alarm__water_leak_sensor_controller__c__set(value);
}


bool alerting__alarm__water_leak_sensor_controller__d__get(void) {
    return coils__get(INTERNAL_COIL__ALARM__WATER_LEAK_SENSOR__C);
}

void alerting__alarm__water_leak_sensor_controller__d__set(bool value) {
    coils__set(INTERNAL_COIL__ALARM__WATER_LEAK_SENSOR__C, value);
}

void alerting__alarm__water_leak_sensor_controller__d__push(bool value) {
    if (value && !alerting__alarm__water_leak_sensor_controller__a__get()) {
        alerting__handle_water_leak_sensor_alert();
    }
    alerting__alarm__water_leak_sensor_controller__d__set(value);
}


// Physical I/O
// -----------------------------------------------------------------------------

void alert_controller__led__set(bool value) {
    coils__set(DISCRETE_OUTPUT__LED__ALARM, value);
}

bool alert_controller__button__get(void) {
    return discrete_inputs__get(DISCRETE_INPUT__BUTTON__ALERTS_RESET);
}


// Logic
// -----------------------------------------------------------------------------

void alert_controller__poll_alerts(void) {
    alerting__alarm__water_leak_sensor_controller__a__push(water_leak_sensor_controller__alarm__a__get());
    alerting__alarm__water_leak_sensor_controller__b__push(water_leak_sensor_controller__alarm__b__get());
    alerting__alarm__water_leak_sensor_controller__c__push(water_leak_sensor_controller__alarm__c__get());
    alerting__alarm__water_leak_sensor_controller__d__push(water_leak_sensor_controller__alarm__d__get());

    alerting__failure__valve_controller__1__push(valve_controller__1__limit_switch__failure__get());
}

// Invoked on every tick of fast timer (every 1ms)
void alert_controller__run(void) {
    alert_controller__poll_alerts();

    alert_controller__led__set(
            alerting__failure__contactor_controller__get()
            || alerting__failure__valve_controller__1__get()
            || alerting__alarm__water_leak_sensor_controller__a__get()
            || alerting__alarm__water_leak_sensor_controller__b__get()
            || alerting__alarm__water_leak_sensor_controller__c__get()
            || alerting__alarm__water_leak_sensor_controller__d__get()
    );
}

void alert_controller__reset_alerts(void) {
    alerting__failure__contactor_controller__set(false);
    alerting__failure__valve_controller__1__set(false);
    alerting__alarm__water_leak_sensor_controller__a__set(water_leak_sensor_controller__alarm__a__get());
    alerting__alarm__water_leak_sensor_controller__b__set(water_leak_sensor_controller__alarm__b__get());
    alerting__alarm__water_leak_sensor_controller__c__set(water_leak_sensor_controller__alarm__c__get());
    alerting__alarm__water_leak_sensor_controller__d__set(water_leak_sensor_controller__alarm__d__get());
    alerting__failure__valve_controller__1__set(valve_controller__1__limit_switch__failure__get());
}

// =============================================================================
// Button listener
// =============================================================================

void alert_controller__button__changed(void) {
    if (alert_controller__button__get()) { // if pressed
        alert_controller__reset_alerts();
    }
}
