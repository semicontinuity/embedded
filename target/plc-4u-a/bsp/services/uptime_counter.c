#include <stdint.h>
#include "services/uptime_counter.h"
#include "services/holding_registers.h"


uint8_t uptime_counter__ticks = 4;


void uptime_counter__run(void) {
    uint8_t ticks = uptime_counter__ticks;
    if (--ticks == 0) {
        ticks = 4;

        uint16_t seconds = holding_registers__buffer__get(0);
        ++seconds;
        if (seconds == 3600) {
            seconds = 0;
            uint16_t hours = holding_registers__buffer__get(1);
            ++hours;
            holding_registers__buffer__set(1, hours);
        }
        holding_registers__buffer__set(0, seconds);
    }
    uptime_counter__ticks = ticks;
}
