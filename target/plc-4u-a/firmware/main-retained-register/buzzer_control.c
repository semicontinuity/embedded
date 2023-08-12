// =============================================================================
// Buzzer controller
//
// There are 2 bits for the state of controller (internal coils):
// - BUZZER__REQUESTED
// - BUZZER__RUNNING
//
// - BUZZER__REQUESTED=0, BUZZER__RUNNING=0: STOPPED
// - BUZZER__REQUESTED=1, BUZZER__RUNNING=0: START_REQUESTED
// - BUZZER__REQUESTED=1, BUZZER__RUNNING=1: RUNNING
// - BUZZER__REQUESTED=0, BUZZER__RUNNING=1: STOP_REQUESTED
// =============================================================================
#include "buzzer_control.h"
#include "services/internal_coils.h"


// Buzzer timeout in seconds
uint8_t buzzer__timeout;


bool buzzer_controller__is_requested(void) {
    return internal_coil__7__get();
}

bool buzzer_controller__is_running(void) {
    return internal_coil__f__get();
}


// Must be invoked on every tick of fast timer (every 1 ms)
void buzzer_controller__on_fast_timer_tick(void) {
}


// Request buzzer start; to be invoked in STOPPED state
void buzzer_controller__start(void) {
}

// Must be invoked every tick of slow timer, if controller is in RUNNING state
void buzzer_controller__run(void) {
}

// Request buzzer stop; to be invoked in RUNNING state
void buzzer_controller__stop(void) {
}

