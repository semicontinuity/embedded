#include "drivers/out/siren2.h"
#include "endpoints/siren2.h"

#include "flags/notifications_pending__siren2.h"
#include "flags/notifications_pending.h"

#include <stdint.h>


INLINE uint8_t siren2__get() {
    return siren2__is_on() ? 1 : 0;
}


INLINE void siren2__set(const uint8_t on) {
    if (on) siren2__on(); else siren2__off();
    notifications_pending__siren2__set(1);
    notifications_pending__set(1);
}
