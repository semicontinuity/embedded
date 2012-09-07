#include <avr/interrupt.h>
#include "cpu/avr/timer2.h"

#ifndef TIMER2_COMPA_vect_attrs
#define TIMER2_COMPA_vect_attrs
#endif

#ifdef TIMER2_COMPA_vect_naked
ISR(TIMER2_COMPA_vect, TIMER2_COMPA_vect_attrs ISR_NAKED) {
#else
ISR(TIMER2_COMPA_vect, TIMER2_COMPA_vect_attrs) {
#endif

    timer2__comp_a__run();

#ifdef TIMER2_COMPA_vect_naked
    reti();
#endif
}
