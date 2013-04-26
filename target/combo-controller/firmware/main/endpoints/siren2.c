#include "drivers/out/siren2.h"
#include "endpoints/siren2.h"

#include "flags/siren2__changed.h"
#include "flags/notifications__pending.h"

#include <stdint.h>


INLINE uint8_t siren2__get() {
    return siren2__is_on() ? 1 : 0;
}


INLINE void siren2__set(const uint8_t on) {
    if (on) siren2__on(); else siren2__off();
    siren2__changed__set(1);
    notifications__pending__set(1);
}
