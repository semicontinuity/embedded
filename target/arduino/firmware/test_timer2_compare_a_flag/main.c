// =============================================================================
// Timer2 compare match flag test.
// Produces square wave signal with 960uS high and low times.
// =============================================================================
#include "cpu/avr/timer2.h"
#include "cpu/avr/gpio.h"
#include <avr/interrupt.h>


void led__init(void) {
    USE_AS_OUTPUT(LED);
}

void led__toggle(void) {
    PORT_REG(SIGNAL_PORT(LED)) ^= SIGNAL_MASK(LED);
}

void schedule(void) {
    timer2__value__set(0);
    timer2__compare_a__value__set(240); // 960uS
    timer2__conf__set(TIMER2_CONF_PRESCALER_64|TIMER2_CONF_WGM_NORMAL);
}


int main(void) {
    led__init();
    schedule();

    for(;;) {
        if (timer2__compare_a__interrupt__pending__get()) {
            timer2__compare_a__interrupt__pending__clear();
            led__toggle();
            schedule();
        }
    }
}
