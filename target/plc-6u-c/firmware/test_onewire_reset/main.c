// =============================================================================
// Timer2 test.
// Produces reset pulses (480uS) and reads presense pulses.
// =============================================================================
#include "cpu/avr/timer2.h"
#include "cpu/avr/gpio.h"

#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "onewire__bus.h"



/** Generates 0->1 transition */
ISR(timer2__compare_a__interrupt__VECTOR, ISR_NAKED) {
    onewire__bus__set(1);
    reti();
}


/** Reads the bit value from the bus */
ISR(timer2__overflow__interrupt__VECTOR, ISR_NAKED) {
    if (onewire__bus__get()) OUT_1(LED); else OUT_0(LED);
    reti();
}


int main(void) {
    USE_AS_OUTPUT(LED);
    onewire__bus__init();
    onewire__bus__set(1);
    _delay_ms(1);

    timer2__compare_a__interrupt__enable();
    timer2__overflow__interrupt__enable();
    timer2__conf__set(TIMER2_CONF_PRESCALER_64|TIMER2_CONF_WGM_NORMAL);

    sei();
    for(;;) {        
        onewire__bus__set(0);
        timer2__value__set(256 - 138);                      // 118
        timer2__compare_a__value__set(256 - 138 + 120);     // 238
        // will count 238-118 = 120 cycles until compare event (480uS), and 18 more cycles (72uS) until flag is set
        
        _delay_ms(1);
    }
}
