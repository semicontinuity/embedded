// =============================================================================
// Roller shutter controller - main module.
// =============================================================================

#include <avr/interrupt.h>
#include <avr/eeprom.h>

#include "kernel.h"
#include "unused.h"
#include "buttons.h"
#include "buttons_scanner.h"
#include "motor.h"
#include "motor_controller.h"
#include "motor_controller_prescaler.h"
#include "system_timer.h"
#include "controller.h"

#include "comm_service__buttons_scanner.h"
#include "comm_service__motor_controller.h"



// =============================================================================
// Implementation of callbacks from other modules (bindings)
// =============================================================================

/**
 * Callback function, called by buttons_scanner__run() when any of the buttons has changed its state.
 */
INLINE void buttons_scanner__status__on_change(void) {
    controller__run();
    comm_service__buttons_scanner__status__broadcast();
}


/**
 * Called by motor_controller__run() when motor_controller__status has been changed.
 */
INLINE void motor_controller__status__on_change(void) {
    comm_service__motor_controller__status__broadcast();
}


/**
 * Callback function, called when the motor status has been changed.
 */
void motor_controller__motor_mode__on_change(void) {
    comm_service__motor_controller__motor_mode__broadcast();
}


/**
 * Callback function, called by system_timer__run() on every system tick.
 */
INLINE void system_timer__on_system_tick(void) {
    buttons_scanner__run();
    motor_controller__prescaler__run();
}


// =============================================================================
// Application
// =============================================================================

inline static void application__init(void) {    
    motor_controller__prescaler__init();
    buttons__init();
    motor__init();
    unused1__init();
    unused2__init();
    unused3__init();
    system_timer__init();
    controller__init();
}

inline static void application__start(void) {
    system_timer__start();
}

inline static void application__stop(void) {
    system_timer__stop();
}


// =============================================================================
// Entry point.
//
// Besides ordinary RESET sources, can be invoked directly by admin handler.
// In that case, the interrupts are disabled, so they need to be enabled.
// TODO: investigate brown-out behaviour (are ports re-initialized?)
// NOTE: possible optimization:
// Ext I/O registers (e.g. USART) accessed with lds/sts.
// =============================================================================
int main(void) {
    if (kernel__mode__is_set()) {
        application__stop();
    }
    else {
        kernel__init();
        kernel__start();

        application__init();
        application__start();
    }

    sei();

    for(;;);
    return 0;
}
