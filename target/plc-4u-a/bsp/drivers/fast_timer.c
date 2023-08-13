#include <stdbool.h>
#include "drivers/fast_timer.h"
#include "cpu/avr/timer0.h"


void fast_timer__init(void) {
    timer0__switch_conf(
            TIMER0_CONF_DEFAULT,
            TIMER0_CONF_WGM_CTC | TIMER0_CONF_TOP(250) | TIMER0_CONF_STOPPED
    );
}

void fast_timer__start(void) {
    // Timer is configured to restart every millisecond. 64*250=16000; 16000/16000000=0.001
    timer0__switch_conf(
            TIMER0_CONF_WGM_CTC | TIMER0_CONF_TOP(250) | TIMER0_CONF_STOPPED,
            TIMER0_CONF_WGM_CTC | TIMER0_CONF_TOP(250) | TIMER0_CONF_PRESCALER_64
    );
}

void fast_timer__stop(void) {
    timer0__switch_conf(
            TIMER0_CONF_WGM_CTC | TIMER0_CONF_TOP(250) | TIMER0_CONF_PRESCALER_64,
            TIMER0_CONF_WGM_CTC | TIMER0_CONF_TOP(250) | TIMER0_CONF_STOPPED
    );
}

bool fast_timer__is_runnable(void) {
    return timer0__compare_a__interrupt__pending__get();
}

void fast_timer__run(void) {
    timer0__compare_a__interrupt__pending__clear();
    fast_timer__do_run();
}
