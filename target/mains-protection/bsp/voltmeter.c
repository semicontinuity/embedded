// =============================================================================
// Mains voltmeter driver.
// Measures the mains voltage at the specified time moment
// after the zero cross event.
// Invoke voltmeter__delayed_run() with the proper delay parameter
// at the moment of the zero cross.
// The measured voltage (raw reading from ADC)
// will be reported to the on_voltage_measured() callback.
// =============================================================================

#include "voltmeter.h"
#include <avr/io.h>
#include <avr/interrupt.h>


typedef union { 
    uint8_t bytes[2]; 
    uint16_t word; 
} CompositeVal; 

#define MAKE_WORD(lo, hi) \
({                        \
    CompositeVal val;     \
    val.bytes[0] = lo;    \
    val.bytes[1] = hi;    \
    val.word;             \
}) 


/**
 * Initialize the voltmeter.
 * Configures ADC and TIMER1.
 */
INLINE void voltmeter__init(void) {
    // Reference voltage at AVCC+AREF, no left adjustment, ADC0.
    ADMUX = (0 << REFS1) | (1 << REFS0) | (0 << ADLAR) | (0 << MUX0);

    // ADC Enable, don't start conversion, no auto conversion, enable interrupt, division factor 64
    //ADCSRA = (1 << ADEN) | (0 << ADSC) | (0 << ADATE) | (1 << ADIE) | (6 << ADPS0);

    // ADC Enable, don't start conversion, auto conversion, enable interrupt, division factor 64
    ADCSRA = (1 << ADEN) | (0 << ADSC) | (1 << ADATE) | (1 << ADIE) | (6 << ADPS0);
    ADCSRB = 5; // T1 Compare match B

    // Disable digital input on ADC0
    DIDR0 = (1 << ADC0D);

    // Enable TIMER1 Compare B interrupt
    TIMSK1 = _BV(OCIE1B);
}


/**
 * Trigger voltage measurement after a specified delay.
 * Program TIMER1 to generate the specified delay (in CPU cycles).
 * After the delay, the Compare B event will trigger ADC conversion,
 * and the interrupt handler will stop the timer (one-shot).
 */
INLINE void voltmeter__delayed_run(const uint16_t delay) {
    OCR1BH = delay >> 8;
    OCR1BL = delay & 0xFF;
    TCCR1B = 1;  // start, no prescaler
}


ISR(ADC_vect) {
    on_voltage_measured (MAKE_WORD(ADCL, ADCH));
}


ISR(TIMER1_COMPB_vect) {
    TCCR1B = 0; // stop the timer
    TCNT1H = 0; // reset the timer value (is it done by hardware already?)
    TCNT1L = 0;
}
