#ifndef __STATE_CHANGE_PULSE_TRANSMITTER_H
#define __STATE_CHANGE_PULSE_TRANSMITTER_H

#include "cpu/avr/gpio.h"

// 1. any change on INT1 generates interrupt (ISC11=0 (default), ISC10=1)
// 2. enable ext int 1
inline void state_change_pulse_transmitter__init(void) {
    USE_AS_OUTPUT(STATE_CHANGE);
}

void state_change_pulse_transmitter__run(void);

void state_change_pulse_transmitter__signal(void);


#endif