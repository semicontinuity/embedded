#include "cpu/avr/pin_change_int2.h"
#include <avr/interrupt.h>

#ifndef PIN_CHANGE_INT2_vect_attrs
#define PIN_CHANGE_INT2_vect_attrs
#endif

#ifdef PIN_CHANGE_INT2_vect_naked
ISR(PCINT2_vect, PIN_CHANGE_INT2_vect_attrs ISR_NAKED) {
#else
ISR(PCINT2_vect, PIN_CHANGE_INT2_vect_attrs) {
#endif

    pin_change_int2__run();

#ifdef PIN_CHANGE_INT2_vect_naked
    reti();
#endif
}
