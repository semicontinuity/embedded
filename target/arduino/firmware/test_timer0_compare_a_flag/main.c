// =============================================================================
// Timer0 compare match flag test.
// Produces square wave signal with 960uS high and low times.
// =============================================================================
#include "cpu/avr/timer0.h"
#include "cpu/avr/gpio.h"
#include <avr/interrupt.h>


void led__init(void) {
    USE_AS_OUTPUT(LED);
}

void led__toggle(void) {
    PORT_REG(SIGNAL_PORT(LED)) ^= SIGNAL_MASK(LED);
}

void schedule(void) {
    timer0__value__set(0);
    timer0__compare_a__value__set(240); // 960uS
    timer0__conf__set(TIMER0_CONF_PRESCALER_64|TIMER0_CONF_WGM_NORMAL);
}


int main(void) {
    led__init();
    schedule();

    for(;;) {
        if (timer0__compare_a__interrupt__pending__get()) {
            timer0__compare_a__interrupt__pending__clear();
            led__toggle();
            schedule();
        }
    }
}
