#include <avr/interrupt.h>
#include "cpu/avr/twi.h"


#ifdef twi__run

void twi__run(void);

#ifndef TWI_vect_attrs
#define TWI_vect_attrs
#endif

#ifdef TWI_vect_naked
ISR(TWI_vect, TWI_vect_attrs ISR_NAKED) {
#else
ISR(TWI_vect, TWI_vect_attrs) {
#endif

    twi__run();

#ifdef TWI_vect_naked
    reti();
#endif
}

#endif
