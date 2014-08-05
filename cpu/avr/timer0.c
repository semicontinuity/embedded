#include <avr/interrupt.h>
#include "cpu/avr/timer0.h"


#ifdef timer0__overflow__run

#if defined(__AVR_AT90S2313__)
#define timer0__overflow__interrupt__VECTOR TIMER0_OVF0_vect
#else
#define timer0__overflow__interrupt__VECTOR TIMER0_OVF_vect
#endif

#ifndef TIMER0_OVERFLOW_vect_attrs
#define TIMER0_OVERFLOW_vect_attrs
#endif

#ifdef TIMER0_OVERFLOW_vect_naked
ISR(timer0__overflow__interrupt__VECTOR, TIMER0_OVERFLOW_vect_attrs ISR_NAKED) {
#else
ISR(timer0__overflow__interrupt__VECTOR, TIMER0_OVERFLOW_vect_attrs) {
#endif

    timer0__overflow__run();

#ifdef TIMER0_OVERFLOW_vect_naked
    reti();
#endif
}

#endif



#ifdef timer0__comp__run

#ifndef TIMER0_COMP_vect_attrs
#define TIMER0_COMP_vect_attrs
#endif

#ifdef TIMER0_COMP_vect_naked
ISR(TIMER0_COMP_vect, TIMER0_COMP_vect_attrs ISR_NAKED) {
#else
ISR(TIMER0_COMP_vect, TIMER0_COMP_vect_attrs) {
#endif

    timer0__comp__run();

#ifdef TIMER0_COMP_vect_naked
    reti();
#endif
}

#endif



#ifdef timer0__comp_a__run

#ifndef TIMER0_COMPA_vect_attrs
#define TIMER0_COMPA_vect_attrs
#endif

#ifdef TIMER0_COMPA_vect_naked
ISR(timer0__compare_a__interrupt__VECTOR, TIMER0_COMPA_vect_attrs ISR_NAKED) {
#else
ISR(timer0__compare_a__interrupt__VECTOR, TIMER0_COMPA_vect_attrs) {
#endif

    timer0__comp_a__run();

#ifdef TIMER0_COMPA_vect_naked
    reti();
#endif
}

#endif



#ifdef timer0__comp_b__run

#ifndef TIMER0_COMPB_vect_attrs
#define TIMER0_COMPB_vect_attrs
#endif

#ifdef TIMER0_COMPB_vect_naked
ISR(TIMER0_COMPB_vect, TIMER0_COMPB_vect_attrs ISR_NAKED) {
#else
ISR(TIMER0_COMPB_vect, TIMER0_COMPB_vect_attrs) {
#endif

    timer0__comp_b__run();

#ifdef TIMER0_COMPB_vect_naked
    reti();
#endif
}

#endif

