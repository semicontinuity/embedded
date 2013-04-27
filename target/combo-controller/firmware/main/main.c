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

#include "flags/notifications_pending.h"
#include "flags/notifications_pending__water_valve.h"
#include "flags/notifications_pending__amplifier_relay.h"
#include "flags/notifications_pending__siren1.h"
#include "flags/notifications_pending__siren2.h"
#include "flags/notifications_pending__motion_sensors.h"
#include "flags/notifications_pending__water_leak_sensors.h"
#include "flags/notifications_pending__alarm__state.h"
#include "flags/notifications_pending__alarm__auth.h"

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
#include "services/water_leak_handler__timer.h"

#include <avr/interrupt.h>


// =============================================================================
// Implementation of callbacks from other modules (bindings)
// =============================================================================

/**
 * Callback function, called by water_leak_sensors_scanner__run() when any of the sensors has changed state.
 */
INLINE void water_leak_sensors_scanner__status__on_change(void) {
    notifications_pending__water_leak_sensors__set(1);
    notifications_pending__set(1);

    water_leak_handler__run();
}


/**
 * Callback function, called by motion_sensors_scanner__run() when any of the sensors has changed state.
 */
INLINE void motion_sensors_scanner__status__on_change(void) {
    notifications_pending__motion_sensors__set(1);
    notifications_pending__set(1);

    if (motion_sensors_scanner__is_active()) alarm__sensor_active();
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
    water_leak_handler__timer__run();
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
    notifications_pending__water_valve__init();
    notifications_pending__amplifier_relay__init();
    notifications_pending__siren1__init();
    notifications_pending__siren2__init();
    notifications_pending__motion_sensors__init();
    notifications_pending__water_leak_sensors__init();
    notifications_pending__alarm__state__init();
    notifications_pending__alarm__auth__init();
    notifications_pending__init();

    // Other drivers
    system_timer__init();
    water_leak_sensors_scanner__init();
    motion_sensors_scanner__init();

    // Services
    alarm__init();
    alarm__auth__init();
    alarm_handler__init();
    water_leak_handler__init();
    console__init();
}


inline static void application__start(void) {
    notifications_pending__water_valve__set(0);
    notifications_pending__amplifier_relay__set(0);
    notifications_pending__siren1__set(0);
    notifications_pending__siren2__set(0);
    notifications_pending__motion_sensors__set(0);
    notifications_pending__water_leak_sensors__set(0);

    // Broadcast these values at startup - for terminals.
    notifications_pending__alarm__state__set(1);
    notifications_pending__alarm__auth__set(1);
    notifications_pending__set(1);

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

    sei();

    // run background tasks
    for(;;) {
        cli();
        comm_service__notifications__1__run();
        sei();
        _delay_us(1);
    }

//    console__run();
    return 0;
}
