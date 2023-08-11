#include <stdint.h>
#include "services/seconds_timer.h"


uint8_t seconds_timer__timeout = 4;


/** Must be invoked on every tick of the slow timer, every 250ms */
void seconds_timer__run(void) {
    if (--seconds_timer__timeout == 0) {
        seconds_timer__timeout = 4;
        seconds_timer__do_run();
    }
}
