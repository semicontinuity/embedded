#ifndef __ALARM_CLIENT_H
#define __ALARM_CLIENT_H

#include "cpu/avr/gpio.h"

// 1. any change on INT1 generates interrupt (ISC11=0 (default), ISC10=1)
// 2. enable ext int 1
inline void alarm_client__init(void) {
    set_bit_in_reg (MCUCR, ISC10);
    set_bit_in_reg (GICR, INT1);
}

void alarm_client__run(void);


#endif