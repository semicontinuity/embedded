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
#include "flags/notifications_pending__emergency__water_sensors__0.h"
#include "flags/notifications_pending__emergency__water_actuators__0.h"
#include "flags/notifications_pending__presense__motion_sensors__0.h"
#include "flags/notifications_pending__media__amplifier__0.h"
#include "flags/notifications_pending__comm__binary__0.h"
#include "flags/notifications_pending__comm__binary__1.h"
#include "flags/notifications_pending__security__state.h"
#include "flags/notifications_pending__security__auth.h"

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

#include "endpoints/emergency__water_sensors__0.h"

#include <avr/interrupt.h>


// =============================================================================
// Implementation of callbacks from other modules (bindings)
// =============================================================================

/**
 * Callback function, called by water_leak_sensors_scanner__run() when any of the sensors has changed state.
 */
INLINE void water_leak_sensors_scanner__status__on_change(void) {
    emergency__water_sensors__0__broadcast();
    water_leak_handler__run();
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
    amplifier_relay__init();
    siren1__init();
    siren2__init();
    water_valve__init();
    unused1__init();
    unused2__init();
    unused3__init();
    unused4__init();
    unused5__init();
    unused6__init();
    unused7__init();
    unused8__init();
    unused9__init();
    unused10__init();
    unused11__init();

    // Input drivers
    water_leak_sensors__init();
    motion_sensors__init();

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
    notifications_pending__emergency__water_sensors__0__set(0);
    notifications_pending__emergency__water_actuators__0__set(0);
    notifications_pending__media__amplifier__0__set(0);
    notifications_pending__comm__binary__0__set(0);
    notifications_pending__comm__binary__1__set(0);
    notifications_pending__presense__motion_sensors__0__set(0);

    // Broadcast these values at startup - for terminals.
    notifications_pending__security__state__set(1);
    notifications_pending__security__auth__set(1);
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
