#include <stdint.h>
#include "services/uptime_counter.h"
#include "services/holding_registers.h"


/** Must be invoked on every tick of the seconds timer */
void uptime_counter__run(void) {
    uint16_t seconds = holding_registers__buffer__get(HOLDING_REGISTER__ADDRESS__UPTIME__SECONDS);
    ++seconds;
    if (seconds == 3600) {
        seconds = 0;
        uint16_t hours = holding_registers__buffer__get(HOLDING_REGISTER__ADDRESS__UPTIME__HOURS);
        ++hours;
        holding_registers__buffer__set(HOLDING_REGISTER__ADDRESS__UPTIME__HOURS, hours);
    }
    holding_registers__buffer__set(HOLDING_REGISTER__ADDRESS__UPTIME__SECONDS, seconds);
}
