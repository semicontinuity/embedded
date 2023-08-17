// =============================================================================
// Alarm controller
//
// Master Alarm LED (in button) is ON, 
// when any of alarm or failure flags is ON. Also, buzzer is requested.
//
// Pressing the button acknowledges and resets all alarm and failure flags.
// Alarm and failure flags may become ON again, set by respective controllers.
// If current alarm and failure flags are acknowledged,
// the LED will turn OFF.
// =============================================================================
#include "contactor_control.h"
#include "valve_controller__1.h"
#include "water_leak_sensors_controller.h"

#include "services/coils.h"
#include "services/discrete_inputs.h"


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

void alarm_controller__run(void) {
    alarm_controller__led__set(
            contactor_control__failure__get()
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
        contactor_control__failure__set(false);
        valve_controller__1__failure__set(false);
        water_leak_sensor_controller__alarm__reset();
    }
}
