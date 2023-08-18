// =============================================================================
// Contactor control
//
// There are 3 internal coils, associated with each valve control channel:
// - ACTIVE
//   Write 1 to request to engage contactor.
//   The contactor coil will be powered or unpowered, depending on target position.
//   Once the commutation finishes (feedback from additional contactor contact),
//   the coil value will be changed to 0.
//   * If the coil value reads as 1, there is commutation in progress.
//   * If the coil value reads as 0, there is no commutation in progress.
//
// - TARGET_POSITION
//   * 1: Closed
//   * 0: Opened
//
// - ERROR:
//   * 1: No feedback about successful commutation within timeout
//   * 0: Commutation has been successful
// =============================================================================
#include "contactor_controller.h"
#include "services/coils.h"
#include "services/discrete_inputs.h"
#include "alert_controller.h"


uint8_t contactor_controller__timeout;


// User interface I/O
// -----------------------------------------------------------------------------

void contactor_controller__led__set(bool on) {
    coils__set(DISCRETE_OUTPUT__LED__CONTACTOR, on);
}

bool contactor_controller__button__get(void) {
    return discrete_inputs__get(DISCRETE_INPUT__BUTTON__CONTACTOR_CONTROL);
}


// Physical I/O
// -----------------------------------------------------------------------------

void contactor_controller__coil__set(bool on) {
    coils__set(DISCRETE_OUTPUT__CONTACTOR__COIL, on);
}

bool contactor_controller__feedback__get(void) {
    return discrete_inputs__get(DISCRETE_INPUT__CONTACTOR__FEEDBACK);
}


// State
// -----------------------------------------------------------------------------

void contactor_controller__active__set(bool value) {
    coils__set(INTERNAL_COIL__CONTACTOR_CONTROL__ACTIVE, value);
}

bool contactor_controller__active__get(void) {
    return coils__get(INTERNAL_COIL__CONTACTOR_CONTROL__ACTIVE);
}


void contactor_controller__target_position__set(bool opened) {
    coils__set(INTERNAL_COIL__CONTACTOR_CONTROL__TARGET_POSITION, opened);
}

bool contactor_controller__target_position__get(void) {
    return coils__get(INTERNAL_COIL__CONTACTOR_CONTROL__TARGET_POSITION);
}


// Logic
// -----------------------------------------------------------------------------

void contactor_controller__activate(void) {
    contactor_controller__active__set(true);
}


void contactor_controller__deactivate(void) {
    contactor_controller__active__set(false);
    contactor_controller__timeout = 0;
}


bool contactor_controller__is_runnable(void) {
    return contactor_controller__active__get();
}

void contactor_controller__run(void) {
    uint8_t timeout = contactor_controller__timeout;
    if (timeout == 0) {
        // Timeout 0 means that the controller has been just activated.
        contactor_controller__timeout = 50;
        contactor_controller__coil__set(contactor_controller__target_position__get());
        alerting__failure__contactor_controller__set(false);
    }
    else {
        --timeout;
        contactor_controller__timeout = timeout;

        bool finished;
        if (timeout == 0) {
            // Reached timeout, but limit switch has not been hit yet.
            alerting__failure__contactor_controller__set(true);
            finished = false;
        } else {
            finished = contactor_controller__target_position__get() == contactor_controller__feedback__get();
        }

        if (alerting__failure__contactor_controller__get() || finished) {
            contactor_controller__deactivate();
        }
    }
}


void contactor_controller__actual_state_renderer__run(void) {
    contactor_controller__led__set(contactor_controller__feedback__get());
}

// =============================================================================
// Button listener
// =============================================================================

void contactor_controller__button__changed(void) {
    if (contactor_controller__button__get()) { // if pressed
        contactor_controller__target_position__set(!contactor_controller__target_position__get());
        contactor_controller__activate();
    }
}
