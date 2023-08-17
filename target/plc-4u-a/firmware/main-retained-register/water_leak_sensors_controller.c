// =============================================================================
// Water leak sensor controller (digital).
//
// When any of the water leak sensors is ON,
// instructs water valve controllers to close valves.
// * Turns on Failure Indicator and Buzzer (for 1 minute)
// =============================================================================
#include <services/holding_registers.h>
#include "water_leak_sensors_controller.h"
#include "services/coils.h"
#include "services/discrete_inputs.h"
#include "valve_controller__1.h"


// Configuration
// -----------------------------------------------------------------------------

bool water_leak_sensor_controller__engagement__is_enabled(void) {
    return holding_registers__buffer__get(HOLDING_REGISTER__ADDRESS__WATER_LEAK_SENSORS_CONTROLLER__ENGAGEMENT__ENABLED);
}


// Physical I/O
// -----------------------------------------------------------------------------

bool water_leak_sensor_controller__sensor__a__get(void) {
    return discrete_inputs__get(DISCRETE_INPUT__WATER_LEAK_SENSOR__A);
}

bool water_leak_sensor_controller__sensor__b__get(void) {
    return discrete_inputs__get(DISCRETE_INPUT__WATER_LEAK_SENSOR__B);
}

bool water_leak_sensor_controller__sensor__c__get(void) {
    return discrete_inputs__get(DISCRETE_INPUT__WATER_LEAK_SENSOR__C);
}

bool water_leak_sensor_controller__sensor__d__get(void) {
    return discrete_inputs__get(DISCRETE_INPUT__WATER_LEAK_SENSOR__D);
}


// State
// -----------------------------------------------------------------------------

void water_leak_sensor_controller__sensor__a__had_leak__set(bool value) {
    coils__set(INTERNAL_COIL__WATER_LEAK_SENSOR__A__HAD_LEAK, value);
}

void water_leak_sensor_controller__sensor__b__had_leak__set(bool value) {
    coils__set(INTERNAL_COIL__WATER_LEAK_SENSOR__B__HAD_LEAK, value);
}

void water_leak_sensor_controller__sensor__c__had_leak__set(bool value) {
    coils__set(INTERNAL_COIL__WATER_LEAK_SENSOR__C__HAD_LEAK, value);
}

void water_leak_sensor_controller__sensor__d__had_leak__set(bool value) {
    coils__set(INTERNAL_COIL__WATER_LEAK_SENSOR__D__HAD_LEAK, value);
}

bool water_leak_sensor_controller__sensor__a__had_leak__get(void) {
    return coils__get(INTERNAL_COIL__WATER_LEAK_SENSOR__A__HAD_LEAK);
}

bool water_leak_sensor_controller__sensor__b__had_leak__get(void) {
    return coils__get(INTERNAL_COIL__WATER_LEAK_SENSOR__B__HAD_LEAK);
}

bool water_leak_sensor_controller__sensor__c__had_leak__get(void) {
    return coils__get(INTERNAL_COIL__WATER_LEAK_SENSOR__C__HAD_LEAK);
}

bool water_leak_sensor_controller__sensor__d__had_leak__get(void) {
    return coils__get(INTERNAL_COIL__WATER_LEAK_SENSOR__D__HAD_LEAK);
}


// Logic
// -----------------------------------------------------------------------------

bool water_leak_sensor_controller__alarm__get(void) {
    return water_leak_sensor_controller__sensor__a__had_leak__get()
    || water_leak_sensor_controller__sensor__b__had_leak__get()
    || water_leak_sensor_controller__sensor__c__had_leak__get()
    || water_leak_sensor_controller__sensor__d__had_leak__get();
}

void water_leak_sensor_controller__alarm__reset(void) {
    water_leak_sensor_controller__sensor__a__had_leak__set(false);
    water_leak_sensor_controller__sensor__b__had_leak__set(false);
    water_leak_sensor_controller__sensor__c__had_leak__set(false);
    water_leak_sensor_controller__sensor__d__had_leak__set(false);
}


void water_leak_sensor_controller__run(void) {
    if (water_leak_sensor_controller__sensor__a__get()) {
        water_leak_sensor_controller__sensor__a__had_leak__set(true);
    }
    if (water_leak_sensor_controller__sensor__b__get()) {
        water_leak_sensor_controller__sensor__b__had_leak__set(true);
    }
    if (water_leak_sensor_controller__sensor__c__get()) {
        water_leak_sensor_controller__sensor__c__had_leak__set(true);
    }
    if (water_leak_sensor_controller__sensor__d__get()) {
        water_leak_sensor_controller__sensor__d__had_leak__set(true);
    }

    if (water_leak_sensor_controller__engagement__is_enabled() && water_leak_sensor_controller__alarm__get()) {
        valve_controller__1__close();
    }
}
