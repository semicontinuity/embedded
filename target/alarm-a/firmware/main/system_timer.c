#include <avr/interrupt.h>
#include <stdint.h>
#include "system_timer.h"


uint8_t fastCounter;

/**
 * This ISR is invoked F_CPU/256/256 times per second (122 @ 8MHz)
 */
ISR(TIMER0_OVF_vect) {
    system_timer__on_system_tick();

    if (fastCounter != 0)
    {
        fastCounter--;
        return;
    }
    fastCounter = (F_CPU/256/256);

    // this place is invoked every 1s    
    system_timer__on_second_tick();
}
    