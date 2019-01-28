#include "state_change_pulse_transmitter.h"
#include "cpu/avr/gpio.h"



uint8_t stateChangePulseTimeout;


void state_change_pulse_transmitter__signal(void) {
    OUT_0(STATE_CHANGE);
    stateChangePulseTimeout = 100;
}


void state_change_pulse_transmitter__run(void) {
    if (stateChangePulseTimeout != 0) // generating pulse
    {
        --stateChangePulseTimeout;
        if (stateChangePulseTimeout == 0) // just reached 0 - pulse generated
        {
            OUT_1(STATE_CHANGE);
        }
    }
}
