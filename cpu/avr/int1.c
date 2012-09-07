#include "int1.h"
#include <avr/interrupt.h>

#ifndef INT1_vect_attrs
#define INT1_vect_attrs
#endif

#ifdef INT1_vect_naked
ISR(INT1_vect, INT1_vect_attrs ISR_NAKED) {
#else
ISR(INT1_vect, INT1_vect_attrs) {
#endif

    int1__run();

#ifdef INT1_vect_naked
    reti();
#endif
}
