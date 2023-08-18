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
//   instructs water valve controllers to close valves.
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

bool water_leak_sensor_controller__engagement__is_enabled(void) {
    return holding_registers__buffer__get(HOLDING_REGISTER__ADDRESS__WATER_LEAK_SENSORS_CONTROLLER__ENGAGEMENT__ENABLED);
}


// Alert handlers
// -----------------------------------------------------------------------------

void alerting__handle_water_leak_sensor_alert(void) {
    buzzer_controller__requested__set(true);

    if (water_leak_sensor_controller__engagement__is_enabled()) {
        valve_controller__1__close();
    }
}

// Failure flags
// -----------------------------------------------------------------------------

bool alerting__failure__contactor_controller__get(void) {
    return coils__get(INTERNAL_COIL__CONTACTOR_CONTROL__FAILURE);
}

void alerting__failure__contactor_controller__set(bool value) {
    if (value && !alerting__failure__contactor_controller__get()) {
        buzzer_controller__requested__set(true);
    }
    coils__set(INTERNAL_COIL__CONTACTOR_CONTROL__FAILURE, value);
}


bool alerting__failure__valve_controller__1__get(void) {
    return coils__get(INTERNAL_COIL__VALVE_CONTROLLER__1__FAILURE);
}

void alerting__failure__valve_controller__1__set(bool value) {
    if (value && !alerting__failure__contactor_controller__get()) {
        buzzer_controller__requested__set(true);
    }
    coils__set(INTERNAL_COIL__VALVE_CONTROLLER__1__FAILURE, value);
}


// Alarm flags
// -----------------------------------------------------------------------------

bool alerting__alarm__water_leak_sensor_controller__a__get(void) {
    return coils__get(INTERNAL_COIL__WATER_LEAK_SENSOR__A__HAD_LEAK);
}

void alerting__alarm__water_leak_sensor_controller__a__set(bool value) {
    if (value && !alerting__alarm__water_leak_sensor_controller__a__get()) {
        alerting__handle_water_leak_sensor_alert();
    }
    coils__set(INTERNAL_COIL__WATER_LEAK_SENSOR__A__HAD_LEAK, value);
}


bool alerting__alarm__water_leak_sensor_controller__b__get(void) {
    return coils__get(INTERNAL_COIL__WATER_LEAK_SENSOR__B__HAD_LEAK);
}

void alerting__alarm__water_leak_sensor_controller__b__set(bool value) {
    if (value && !alerting__alarm__water_leak_sensor_controller__a__get()) {
        alerting__handle_water_leak_sensor_alert();
    }
    coils__set(INTERNAL_COIL__WATER_LEAK_SENSOR__B__HAD_LEAK, value);
}


bool alerting__alarm__water_leak_sensor_controller__c__get(void) {
    return coils__get(INTERNAL_COIL__WATER_LEAK_SENSOR__C__HAD_LEAK);
}

void alerting__alarm__water_leak_sensor_controller__c__set(bool value) {
    if (value && !alerting__alarm__water_leak_sensor_controller__a__get()) {
        alerting__handle_water_leak_sensor_alert();
    }
    coils__set(INTERNAL_COIL__WATER_LEAK_SENSOR__C__HAD_LEAK, value);
}


bool alerting__alarm__water_leak_sensor_controller__d__get(void) {
    return coils__get(INTERNAL_COIL__WATER_LEAK_SENSOR__D__HAD_LEAK);
}

void alerting__alarm__water_leak_sensor_controller__d__set(bool value) {
    if (value && !alerting__alarm__water_leak_sensor_controller__a__get()) {
        alerting__handle_water_leak_sensor_alert();
    }
    coils__set(INTERNAL_COIL__WATER_LEAK_SENSOR__D__HAD_LEAK, value);
}


// Physical I/O
// -----------------------------------------------------------------------------

void alert_controller__led__set(bool value) {
    coils__set(DISCRETE_OUTPUT__LED__ALARM, value);
}

bool alert_controller__button__get(void) {
    return discrete_inputs__get(DISCRETE_INPUT__BUTTON__ALARM);
}


// Logic
// -----------------------------------------------------------------------------

void alert_controller__poll_alerts(void) {
    alerting__alarm__water_leak_sensor_controller__a__set(water_leak_sensor_controller__alarm__a__get());
    alerting__alarm__water_leak_sensor_controller__b__set(water_leak_sensor_controller__alarm__b__get());
    alerting__alarm__water_leak_sensor_controller__c__set(water_leak_sensor_controller__alarm__c__get());
    alerting__alarm__water_leak_sensor_controller__d__set(water_leak_sensor_controller__alarm__d__get());
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

// =============================================================================
// Button listener
// =============================================================================

/**
 * TODO:
 * Should memorize the combination of alarm conditions at the time of button press.
 * If conditions are the same, do not light up LED and trigger buzzer.
 */
void alert_controller__button__changed(void) {
    if (alert_controller__button__get()) { // if pressed
        alerting__failure__contactor_controller__set(false);
//        valve_controller__1__failure__set(false);
    }
}
