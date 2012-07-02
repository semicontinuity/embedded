#ifndef __DEVICE_H
#define __DEVICE_H

// internal RC oscillator
#define F_CPU 8000000UL

// MCU peripherals
// CS of MCP2515 is connected to SS
#include "cpu/avr/spi.h"

// user signals
#include "signal__pwm.h"
#include "signal__led.h"


#include "config__usart.h"
#include "config__spi.h"
#include "config__can.h"

#endif