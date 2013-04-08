// =============================================================================
// Roller shutter controller - main module.
// =============================================================================

#include <avr/interrupt.h>
#include <avr/eeprom.h>

#include "kernel.h"
#include "unused.h"
#include "seconds_timer.h"
#include "system_timer.h"
#include "water_leak_handler.h"
#include "water_leak_sensors.h"
#include "water_leak_sensors_scanner.h"
#include "water_valve.h"

#include "comm_service__water_valve_controller.h"

#include "console_service.h"


// =============================================================================
// Implementation of callbacks from other modules (bindings)
// =============================================================================

/**
 * Callback function, called by water_leak_sensors_scanner__run() when any of the sensors has changed state.
 */
INLINE void water_leak_sensors_scanner__status__on_change(void) {
    water_leak_handler__run();
}

/**
 * Called by motor_controller__run() when motor_controller__status has been changed.
 */
INLINE void water_valve_controller__value__on_change(void) {
    comm_service__water_valve_controller__value__broadcast();
}


/**
 * Called on every system tick.
 */
INLINE void system_timer__out__run(void) {
    water_leak_sensors_scanner__run();
    seconds_timer__run();
}

/**
 * Called every second
 */ 
INLINE void seconds_timer__out__run(void) {
}


// =============================================================================
// Application
// =============================================================================

inline static void application__init(void) {
    console_service__init();

    water_leak_sensors__init();
    water_leak_sensors_scanner__init();

    water_valve__init();
    water_valve_controller__init();

//    unused1__init();
//    unused2__init();
//    unused3__init();
    water_leak_handler__init();
    system_timer__init();
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

    //for(;;);
    console_service__run();

    return 0;
}
