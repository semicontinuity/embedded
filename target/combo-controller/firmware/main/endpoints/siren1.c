#include "drivers/out/siren1.h"
#include "endpoints/siren1.h"

#include "flags/siren1__changed.h"
#include "flags/notifications__pending.h"

#include <stdint.h>


INLINE uint8_t siren1__get() {
    return siren1__is_on() ? 1 : 0;
}


INLINE void siren1__set(const uint8_t on) {
    if (on) siren1__on(); else siren1__off();
    siren1__changed__set(1);
    notifications__pending__set(1);
}
