#ifndef __DEVICE_H
#define __DEVICE_H

// internal RC oscillator
#define F_CPU 8000000UL

#define VOLTAGE_MULTIPLIER 52650UL

#include "signal/led_green.h"
#include "signal/led_red.h"

#include "signal/display_anode1.h"
#include "signal/display_anode2.h"
#include "signal/display_anode3.h"
#include "signal/display_segments.h"

#include "signal/buttons.h"
#include "signal/relay.h"
#include "signal/buzzer.h"

//#include "config__uart.h"
//#include "config__debug.h"


#endif