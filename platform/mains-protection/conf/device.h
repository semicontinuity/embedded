#ifndef __DEVICE_H
#define __DEVICE_H

// internal RC oscillator
#define F_CPU 8000000UL

#define VOLTAGE_MULTIPLIER 52650UL

#include "signal__led_green.h"
#include "signal__led_red.h"

#include "signal__display_anode1.h"
#include "signal__display_anode2.h"
#include "signal__display_anode3.h"
#include "signal__display_segments.h"

#include "signal__buttons.h"
#include "signal__relay.h"
#include "signal__buzzer.h"

//#include "config__uart.h"
//#include "config__debug.h"


#endif