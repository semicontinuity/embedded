#include <stdint.h>
#include "services/slow_timer.h"


uint8_t slow_timer__timeout = 250;


void slow_timer__run(void) {
    if (--slow_timer__timeout == 0) {
        slow_timer__timeout = 250;
        slow_timer__do_run();
    }
}
