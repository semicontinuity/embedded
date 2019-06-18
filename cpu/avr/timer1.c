#include <avr/interrupt.h>
#include "cpu/avr/timer1.h"


#ifdef timer1__comp_a__run

#ifndef TIMER1_COMPA_vect_attrs
#define TIMER1_COMPA_vect_attrs
#endif

#ifdef TIMER1_COMPA_vect_naked
ISR(timer1__compare_a__interrupt__VECTOR, TIMER0_COMPA_vect_attrs ISR_NAKED) {
#else
ISR(timer1__compare_a__interrupt__VECTOR, TIMER0_COMPA_vect_attrs) {
#endif

    timer1__comp_a__run();

#ifdef TIMER1_COMPA_vect_naked
    reti();
#endif
}

#endif



#ifdef timer1__comp_b__run

#ifndef TIMER1_COMPB_vect_attrs
#define TIMER1_COMPB_vect_attrs
#endif

#ifdef TIMER1_COMPB_vect_naked
ISR(TIMER1_COMPB_vect, TIMER1_COMPB_vect_attrs ISR_NAKED) {
#else
ISR(TIMER1_COMPB_vect, TIMER1_COMPB_vect_attrs) {
#endif

    timer1__comp_b__run();

#ifdef TIMER1_COMPB_vect_naked
    reti();
#endif
}

#endif

