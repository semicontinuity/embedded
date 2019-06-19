#include <avr/interrupt.h>
#include "cpu/avr/timer2.h"


#ifdef timer2__overflow__run

#ifndef TIMER2_OVERFLOW_vect_attrs
#define TIMER2_OVERFLOW_vect_attrs
#endif

#ifdef TIMER2_OVERFLOW_vect_naked
ISR(timer2__overflow__interrupt__VECTOR, TIMER2_OVERFLOW_vect_attrs ISR_NAKED) {
#else
ISR(timer2__overflow__interrupt__VECTOR, TIMER2_OVERFLOW_vect_attrs) {
#endif

    timer2__overflow__run();

#ifdef TIMER2_OVERFLOW_vect_naked
    reti();
#endif
}

#endif


#ifdef timer2__comp_a__run

extern void timer2__comp_a__run(void);

#ifndef TIMER2_COMPA_vect_attrs
#define TIMER2_COMPA_vect_attrs
#endif

#ifdef TIMER2_COMPA_vect_naked
ISR(timer2__compare_a__interrupt__VECTOR, TIMER2_COMPA_vect_attrs ISR_NAKED) {
#else
ISR(timer2__compare_a__interrupt__VECTOR, TIMER2_COMPA_vect_attrs) {
#endif

    timer2__comp_a__run();

#if defined(TIMER2_COMPA_vect_naked) && !defined(TIMER2_COMPA_vect_no_reti)
    reti();
#endif
}

#endif



#ifdef timer2__comp_b__run

extern void timer2__comp_b__run(void);

#ifndef TIMER2_COMPB_vect_attrs
#define TIMER2_COMPB_vect_attrs
#endif

#ifdef TIMER2_COMPB_vect_naked
ISR(timer2__compare_b__interrupt__VECTOR, TIMER2_COMPB_vect_attrs ISR_NAKED) {
#else
ISR(timer2__compare_b__interrupt__VECTOR, TIMER2_COMPB_vect_attrs) {
#endif

    timer2__comp_b__run();

#if defined(TIMER2_COMPB_vect_naked) && !defined(TIMER2_COMPB_vect_no_reti)
    reti();
#endif
}

#endif

