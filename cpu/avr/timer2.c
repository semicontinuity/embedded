#include <avr/interrupt.h>
#include "cpu/avr/timer2.h"


#ifdef timer2__comp__run

#ifndef TIMER2_COMP_vect_attrs
#define TIMER2_COMP_vect_attrs
#endif

#ifdef TIMER2_COMP_vect_naked
ISR(TIMER2_COMP_vect, TIMER2_COMP_vect_attrs ISR_NAKED) {
#else
ISR(TIMER2_COMP_vect, TIMER2_COMP_vect_attrs) {
#endif

    timer2__comp__run();

#ifdef TIMER2_COMP_vect_naked
    reti();
#endif
}

#endif



#ifdef timer2__comp_a__run

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

#endif



#ifdef timer2__comp_b__run

#ifndef TIMER2_COMPB_vect_attrs
#define TIMER2_COMPB_vect_attrs
#endif

#ifdef TIMER2_COMPB_vect_naked
ISR(TIMER2_COMPB_vect, TIMER2_COMPB_vect_attrs ISR_NAKED) {
#else
ISR(TIMER2_COMPB_vect, TIMER2_COMPB_vect_attrs) {
#endif

    timer2__comp_b__run();

#ifdef TIMER2_COMPB_vect_naked
    reti();
#endif
}

#endif

