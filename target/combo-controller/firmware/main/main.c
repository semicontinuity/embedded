// =============================================================================
// Combo controller - main module.
// =============================================================================


#include "drivers/out/amplifier_relay.h"
#include "drivers/out/siren1.h"
#include "drivers/out/siren2.h"
#include "drivers/out/water_valve.h"
#include "drivers/out/unused.h"

#include "drivers/in/water_leak_sensors.h"
#include "drivers/in/motion_sensors.h"

#include "flags/notifications__pending.h"
#include "flags/water_valve__changed.h"
#include "flags/amplifier_relay__changed.h"
#include "flags/siren1__changed.h"
#include "flags/siren2__changed.h"
#include "flags/motion_sensors__changed.h"
#include "flags/water_leak_sensors__changed.h"
#include "flags/alarm__state__changed.h"

#include "kernel.h"


#include "drivers/system_timer.h"

#include "motion_sensors_scanner.h"
#include "water_leak_sensors_scanner.h"
#include "comm_service__notifications__1.h"
//#include "services/console.h"

#include "services/alarm.h"
#include "services/alarm__timer.h"
#include "services/alarm__auth.h"
#include "services/seconds_timer.h"
#include "services/alarm_handler.h"
#include "services/water_leak_handler.h"

#include <avr/interrupt.h>


// =============================================================================
// Implementation of callbacks from other modules (bindings)
// =============================================================================

/**
 * Callback function, called by water_leak_sensors_scanner__run() when any of the sensors has changed state.
 */
INLINE void water_leak_sensors_scanner__status__on_change(void) {
    water_leak_sensors__changed__set(1);
    notifications__pending__set(1);

    water_leak_handler__run();
}


/**
 * Callback function, called by motion_sensors_scanner__run() when any of the sensors has changed state.
 */
INLINE void motion_sensors_scanner__status__on_change(void) {
    motion_sensors__changed__set(1);
    notifications__pending__set(1);
}


/**
 * Called on every system tick.
 */
INLINE void system_timer__out__run(void) {
    water_leak_sensors_scanner__run();
    motion_sensors_scanner__run();
    seconds_timer__run();
}

/**
 * Called every second.
 */ 
INLINE void seconds_timer__out__run(void) {
    alarm__timer__run();
}


// =============================================================================
// Application
// =============================================================================

inline static void application__init(void) {
    // Output drivers
    unused1__init();
    unused2__init();
    amplifier_relay__init();
    siren1__init();
    siren2__init();
    water_valve__init();

    // Input drivers
    water_leak_sensors__init();
    motion_sensors__init();

    // Flags
    notifications__pending__init();
    water_valve__changed__init();
    amplifier_relay__changed__init();
    siren1__changed__init();
    siren2__changed__init();
    motion_sensors__changed__init();
    water_leak_sensors__changed__init();
    alarm__state__changed__init();

    // Other drivers
    system_timer__init();
    water_leak_sensors_scanner__init();
    motion_sensors_scanner__init();

    // Services
    alarm__init();
    alarm__auth__init();
    alarm_handler__init();
    water_leak_handler__init();
    // console_service__init();
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
//    if (kernel__mode__is_set()) {
//        application__stop();
//    }
//    else {
        kernel__init();
        kernel__start();

        application__init();
        application__start();
//    }

    //sei();

    // run background tasks
    for(;;) {
        cli();
        comm_service__notifications__1__run();
        sei();
    }

//    console_service__run();
    return 0;
}
