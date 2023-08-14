#include "drivers/buzzer_timer.h"
#include "drivers/out/buzzer.h"
#include "cpu/avr/timer2.h"


void buzzer_timer__init(void) {
    timer2__switch_conf(
            TIMER2_CONF_DEFAULT,
            TIMER2_CONF_WGM_CTC | TIMER2_CONF_TOP(250) | TIMER2_CONF_STOPPED
    );
}

void buzzer_timer__start(void) {
    // Timer is configured to restart every millisecond. 64*250=16000; 16000/16000000=0.001
    timer2__switch_conf(
            TIMER2_CONF_WGM_CTC | TIMER2_CONF_TOP(250) | TIMER2_CONF_STOPPED,
            TIMER2_CONF_WGM_CTC | TIMER2_CONF_TOP(250) | TIMER2_CONF_PRESCALER_64
    );
}

void buzzer_timer__stop(void) {
    timer2__switch_conf(
            TIMER2_CONF_WGM_CTC | TIMER2_CONF_TOP(250) | TIMER2_CONF_PRESCALER_64,
            TIMER2_CONF_WGM_CTC | TIMER2_CONF_TOP(250) | TIMER2_CONF_STOPPED
    );
}

void buzzer_timer__run(void) {
    // rewrite for ATMega16
    buzzer__toggle();
}
