#include "cpu/avr/int0.h"
#include <avr/interrupt.h>


#ifndef INT0_vect_attrs
#define INT0_vect_attrs
#endif

#ifdef INT0_vect_naked
ISR(INT0_vect, INT0_vect_attrs ISR_NAKED) {
#else
ISR(INT0_vect, INT0_vect_attrs) {
#endif

    int0__run();

#ifdef INT0_vect_naked
    reti();
#endif
}
