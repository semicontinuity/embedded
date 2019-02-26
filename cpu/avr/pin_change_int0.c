#include "cpu/avr/pin_change_int0.h"
#include <avr/interrupt.h>

#ifndef PIN_CHANGE_INT0_vect_attrs
#define PIN_CHANGE_INT0_vect_attrs
#endif

#ifdef PIN_CHANGE_INT0_vect_naked
ISR(PCINT0_vect, PIN_CHANGE_INT0_vect_attrs ISR_NAKED) {
#else
ISR(PCINT0_vect, PIN_CHANGE_INT0_vect_attrs) {
#endif

    pin_change_int0__run();

#ifdef PIN_CHANGE_INT0_vect_naked
    reti();
#endif
}
