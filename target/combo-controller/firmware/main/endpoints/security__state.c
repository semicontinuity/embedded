#include "services/alarm.h"
#include "endpoints/security__state.h"

#include "flags/notifications_pending__security__state.h"
#include "flags/notifications_pending.h"

#include "drivers/net/can/mcp251x/tx.h"
#include "kernel.h"

#include <stdint.h>


INLINE void security__state__broadcast(void) {
    notifications_pending__security__state__set(1);
    notifications_pending__set(1);
}

INLINE void security__state__do_broadcast(void) {
    notifications_pending__security__state__set(0);
    mcp2515__tx__txb1__send_report(UCAN__PID__SECURITY__STATE, 1, (uint8_t*)&alarm__state);
}



// data[0]: 0=DISARM, 1=ARM - corresponds to values of security__state
INLINE void security__state__set_data(const uint8_t* data) {
    const uint8_t new_state = data[0];
    if (new_state == ALARM__STATE__DISARMED) {
        alarm__disarm();
    }
    else if (new_state == ALARM__STATE__ARMING) {
        alarm__arm();
    }
}

/**
 * Callback implementation
 */
INLINE void alarm__state__on_change(void) {
    security__state__broadcast();
}
