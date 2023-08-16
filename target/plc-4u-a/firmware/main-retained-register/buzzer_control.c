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
#include <services/holding_registers.h>
#include "buzzer_control.h"
#include "drivers/out/buzzer.h"
#include "drivers/buzzer_timer.h"
#include "services/internal_coils.h"


// Buzzer timeout in slow timer ticks
uint8_t buzzer__timeout;


bool buzzer_controller__is_requested(void) {
    return internal_coil__get(INTERNAL_COIL__BUZZER_CONTROLLER__REQUESTED);
}

void buzzer_controller__requested__set(bool requested) {
    internal_coil__set(INTERNAL_COIL__BUZZER_CONTROLLER__REQUESTED, requested);
}

bool buzzer_controller__is_running(void) {
    return internal_coil__get(INTERNAL_COIL__BUZZER_CONTROLLER__RUNNING);
}

void buzzer_controller__running__set(bool running) {
    internal_coil__set(INTERNAL_COIL__BUZZER_CONTROLLER__RUNNING, running);
}


// Request buzzer start; to be invoked in STOPPED state
void buzzer_controller__start_requested(void) {
    buzzer__timeout = holding_registers__buffer__get(HOLDING_REGISTER__ADDRESS__BUZZER__DURATION_TICKS);
    buzzer_controller__running__set(true);
    buzzer_timer__start();
}

// Must be invoked every tick of slow timer, if controller is in RUNNING state
void buzzer_controller__run(void) {
    uint8_t timeout = buzzer__timeout;
    if (timeout == 0) {
        buzzer_timer__stop();
        buzzer__off();
        buzzer_controller__running__set(false);
        buzzer_controller__requested__set(false);
    } else {
        --timeout;
        buzzer__timeout = timeout;
    }
}

// Request buzzer stop; to be invoked in RUNNING state
void buzzer_controller__stop_requested(void) {
    buzzer__timeout = 0;
}


// Must be invoked on every tick of fast timer (every 1 ms)
void buzzer_controller__on_slow_timer_tick(void) {
    if (buzzer_controller__is_running()) {
        if (!buzzer_controller__is_requested()) {
            buzzer_controller__stop_requested();
        }
        buzzer_controller__run();
    } else {
        if (buzzer_controller__is_requested()) {
            buzzer_controller__start_requested();
        }
    }
}

void buzzer_controller__init(void) {
    buzzer__timeout = 0;
}