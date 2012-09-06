#include "int0.h"
#include <avr/interrupt.h>

#ifndef INT0_vect_attrs
#define INT0_vect_attrs
#endif

ISR(INT0_vect, INT0_vect_attrs) {
    int0__run();
}
