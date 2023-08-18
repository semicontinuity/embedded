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
#include <services/holding_registers.h>
#include "contactor_controller.h"
#include "services/coils.h"
#include "services/discrete_inputs.h"
#include "alert_controller.h"


uint8_t contactor_controller__timeout;


// Configuration
// -----------------------------------------------------------------------------

uint8_t contactor_controller__timeout_ms(void) {
    return holding_registers__buffer__get(HOLDING_REGISTER__ADDRESS__CONTACTOR__TIMEOUT_MS);
}


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

void contactor_controller__target_position__set(bool opened) {
    coils__set(INTERNAL_COIL__CONTACTOR_CONTROLLER__TARGET_POSITION, opened);
}

bool contactor_controller__target_position__get(void) {
    return coils__get(INTERNAL_COIL__CONTACTOR_CONTROLLER__TARGET_POSITION);
}


void contactor_controller__requested__set(bool running) {
    coils__set(INTERNAL_COIL__CONTACTOR_CONTROLLER__REQUESTED, running);
}

bool contactor_controller__is_requested(void) {
    return coils__get(INTERNAL_COIL__CONTACTOR_CONTROLLER__REQUESTED);
}


void contactor_controller__running__set(bool running) {
    coils__set(INTERNAL_COIL__CONTACTOR_CONTROLLER__RUNNING, running);
}

bool contactor_controller__is_running(void) {
    return coils__get(INTERNAL_COIL__CONTACTOR_CONTROLLER__RUNNING);
}


// Logic
// -----------------------------------------------------------------------------

void contactor_controller__start_requested(void) {
    contactor_controller__timeout = contactor_controller__timeout_ms();
    contactor_controller__coil__set(contactor_controller__target_position__get());
    alerting__failure__contactor_controller__push(false);
    contactor_controller__running__set(true);
}

void contactor_controller__run(void) {
    uint8_t timeout = contactor_controller__timeout;
    if (timeout == 0) {
        // Reached timeout, but limit switch has not been hit yet.
        alerting__failure__contactor_controller__push(true);
        contactor_controller__running__set(false);
        contactor_controller__requested__set(false);
        // Contactor coil output remains in the target state, regardless of failure
        // (Perhaps, make usage of feedback configurable)
    } else {
        --timeout;
        contactor_controller__timeout = timeout;
        // Normally, target state must be reached before timeout
        if (contactor_controller__target_position__get() == contactor_controller__feedback__get()) {
            contactor_controller__running__set(false);
            contactor_controller__requested__set(false);
        }
    }
}

void contactor_controller__stop_requested(void) {
    // cancelling request makes little sense
    contactor_controller__timeout = 0;
}


// Must be invoked on every tick of fast timer (every 1 ms)
void contactor_controller__on_slow_timer_tick(void) {
    if (contactor_controller__is_running()) {
        if (!contactor_controller__is_requested()) {
            contactor_controller__stop_requested();
        }
        contactor_controller__run();
    } else {
        if (contactor_controller__is_requested()) {
            contactor_controller__start_requested();
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
        contactor_controller__requested__set(true);
    }
}
