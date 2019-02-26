#include "cpu/avr/pin_change_int1.h"
#include <avr/interrupt.h>

#ifndef PIN_CHANGE_INT1_vect_attrs
#define PIN_CHANGE_INT1_vect_attrs
#endif

#ifdef PIN_CHANGE_INT1_vect_naked
ISR(PCINT1_vect, PIN_CHANGE_INT1_vect_attrs ISR_NAKED) {
#else
ISR(PCINT1_vect, PIN_CHANGE_INT1_vect_attrs) {
#endif

    pin_change_int1__run();

#ifdef PIN_CHANGE_INT1_vect_naked
    reti();
#endif
}
