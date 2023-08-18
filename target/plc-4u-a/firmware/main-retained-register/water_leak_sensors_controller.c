// =============================================================================
// Water leak sensor controller (digital).
// =============================================================================
#include <services/holding_registers.h>
#include "water_leak_sensors_controller.h"
#include "services/discrete_inputs.h"


// Configuration
// -----------------------------------------------------------------------------

bool water_leak_sensor_controller__sensor__a__is_enabled(void) {
    return holding_registers__buffer__get(HOLDING_REGISTER__ADDRESS__WATER_LEAK_SENSOR__A__ENABLED);
}

bool water_leak_sensor_controller__sensor__b__is_enabled(void) {
    return holding_registers__buffer__get(HOLDING_REGISTER__ADDRESS__WATER_LEAK_SENSOR__B__ENABLED);
}

bool water_leak_sensor_controller__sensor__c__is_enabled(void) {
    return holding_registers__buffer__get(HOLDING_REGISTER__ADDRESS__WATER_LEAK_SENSOR__C__ENABLED);
}

bool water_leak_sensor_controller__sensor__d__is_enabled(void) {
    return holding_registers__buffer__get(HOLDING_REGISTER__ADDRESS__WATER_LEAK_SENSOR__D__ENABLED);
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


// Logic
// -----------------------------------------------------------------------------

bool water_leak_sensor_controller__alarm__a__get(void) {
    return water_leak_sensor_controller__sensor__a__is_enabled() && water_leak_sensor_controller__sensor__a__get();
}

bool water_leak_sensor_controller__alarm__b__get(void) {
    return water_leak_sensor_controller__sensor__b__is_enabled() && water_leak_sensor_controller__sensor__b__get();
}

bool water_leak_sensor_controller__alarm__c__get(void) {
    return water_leak_sensor_controller__sensor__c__is_enabled() && water_leak_sensor_controller__sensor__c__get();
}

bool water_leak_sensor_controller__alarm__d__get(void) {
    return water_leak_sensor_controller__sensor__d__is_enabled() && water_leak_sensor_controller__sensor__d__get();
}


void water_leak_sensor_controller__run(void) {
}
