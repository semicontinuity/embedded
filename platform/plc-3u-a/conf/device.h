#ifndef __DEVICE_H
#define __DEVICE_H

// internal RC oscillator
#define F_CPU 8000000UL

// user signals
#include "signal__pwm.h"
#include "signal__led.h"

#include "config__usart.h"
#include "config__spi.h"
#include "config__can_selector.h"
#include "config__can.h"

#endif