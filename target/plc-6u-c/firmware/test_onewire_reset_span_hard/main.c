// =============================================================================
// 1-wire reset pulse test.
// Combined test for Timer0 and Timer2.
// =============================================================================
#include "cpu/avr/timer0.h"
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
    USE_AS_OUTPUT(LED2); 
    onewire__bus__init();
    onewire__bus__set(1);
    _delay_ms(1);
    

    for(;;) {
        OUT_0(LED2);
        timer2__compare_a__interrupt__enable();
        timer2__overflow__interrupt__enable();
        
        onewire__bus__set(0);

        // count from 118 to 238 = 120 cycles until compare event (480uS), and 18 more cycles to 256 (72uS) until flag is set
        timer2__value__set(118);	// 256 - 138
        timer2__compare_a__value__set(238);     // 256 - 138 + 120
        timer2__conf__set(TIMER2_CONF_PRESCALER_64|TIMER2_CONF_WGM_NORMAL);

        // count from 16 to 256 = 240 cycles to overflow condition (960uS)
        timer0__value__set(16);	
        timer0__conf__set(TIMER0_CONF_PRESCALER_64|TIMER0_CONF_WGM_NORMAL);

        sei();
        while (!timer0__overflow__interrupt__pending__get());
        cli();

        timer0__overflow__interrupt__pending__clear();
        timer0__conf__set(TIMER0_CONF_STOPPED);
        timer2__conf__set(TIMER0_CONF_STOPPED);
        OUT_1(LED2);

        _delay_us(40);
    }

}
