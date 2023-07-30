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
#include "contactor_control.h"
#include "services/internal_coils.h"
#include "services/discrete_inputs.h"
#include "services/discrete_outputs.h"


uint8_t contactor_control__timeout;


void contactor_control__active__set(bool value) {
    internal_coil__4__set(value);
}

bool contactor_control__active__get(void) {
    return internal_coil__4__get();
}


void contactor_control__target_position__set(bool opened) {
    internal_coil__5__set(opened);
}

bool contactor_control__target_position__get(void) {
    return internal_coil__5__get();
}


void contactor_control__failure__set(bool value) {
    internal_coil__a__set(value);
}

bool contactor_control__failure__get(void) {
    return internal_coil__a__get();
}


void contactor_control__coil__set(bool on) {
    discrete_output__4__set(on);
}

void contactor_control__led__on__set(bool on) {
    discrete_output__e__set(on);
}


bool contactor_control__feedback__get(void) {
    return discrete_inputs__8__get();
}


void contactor_control__activate(void) {
    contactor_control__active__set(true);
}


void contactor_control__deactivate(void) {
    contactor_control__active__set(false);
    contactor_control__timeout = 0;
}


bool contactor_control__is_runnable(void) {
    return contactor_control__active__get();
}

void contactor_control__run(void) {
    uint8_t timeout = contactor_control__timeout;
    if (timeout == 0) {
        // Timeout 0 means that the controller has been just activated.
        contactor_control__timeout = 50;
        contactor_control__coil__set(contactor_control__target_position__get());
        contactor_control__failure__set(false);
    }
    else {
        --timeout;
        contactor_control__timeout = timeout;

        bool finished;
        if (timeout == 0) {
            // Reached timeout, but limit switch has not been hit yet.
            contactor_control__failure__set(true);
            finished = false;
        } else {
            finished = contactor_control__target_position__get() == contactor_control__feedback__get();
        }

        if (contactor_control__failure__get() || finished) {
            contactor_control__deactivate();
        }
    }
}


void contactor_control__actual_state_renderer__run(void) {
    contactor_control__led__on__set(contactor_control__feedback__get());
}

// =============================================================================
// Button listener
// =============================================================================

void contactor_control__button__changed() {
    if (contactor_control__button__get()) {
        // if pressed
        contactor_control__target_position__set(!contactor_control__target_position__get());
        contactor_control__activate();
    }
}
