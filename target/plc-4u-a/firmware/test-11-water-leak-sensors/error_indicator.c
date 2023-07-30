// =============================================================================
// Error indicator
//
// Error LED (in button) is ON, when any of error flags is ON.
// Pressing the button resets all error flags, and the LED becomes OFF.
// =============================================================================
#include "contactor_control.h"
#include "valve_controller__1.h"

#include "services/discrete_outputs.h"


void error_indicator__led__set(bool on) {
    discrete_output__f__set(on);
}

void error_indicator__run(void) {
    error_indicator__led__set(contactor_control__error__get() || valve_controller__1__error__get());
}

// =============================================================================
// Button listener
// =============================================================================

void error_indicator__button__changed() {
    if (error_indicator__button__get()) {
        // if pressed
        contactor_control__error__set(false);
        valve_controller__1__error__set(false);
    }
}
