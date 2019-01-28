#include "cpu/avr/int2.h"
#include <avr/interrupt.h>

#ifndef INT2_vect_attrs
#define INT2_vect_attrs
#endif

#ifdef INT2_vect_naked
ISR(INT2_vect, INT2_vect_attrs ISR_NAKED) {
#else
ISR(INT2_vect, INT2_vect_attrs) {
#endif

    int2__run();

#ifdef INT2_vect_naked
    reti();
#endif
}
