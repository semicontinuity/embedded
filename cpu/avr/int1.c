#include "int1.h"
#include <avr/interrupt.h>

#ifndef INT1_vect_attrs
#define INT1_vect_attrs
#endif

ISR(INT1_vect, INT1_vect_attrs) {
    int1__run();
}
