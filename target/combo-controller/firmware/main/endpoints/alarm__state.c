#include "services/alarm.h"
#include "endpoints/alarm__state.h"

#include "flags/notifications_pending__alarm__state.h"
#include "flags/notifications_pending.h"

#include <stdint.h>


INLINE uint8_t alarm__state__get_data(uint8_t **data) {
    *data = &alarm__state;
    return sizeof(alarm__state);
}


INLINE void alarm__state__set_data(const uint8_t* data) {
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
    notifications_pending__alarm__state__set(1);
    notifications_pending__set(1);
}
