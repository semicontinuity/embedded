#ifndef __DEVICE_H
#define __DEVICE_H

// internal RC oscillator
#define F_CPU 8000000UL

// MCU peripherals


// fixed MCU signals
// CS of MCP2515 is connected to SS
//#include "mega8/signal__tx.h"
//#include "mega8/signal__mosi.h"
//#include "mega8/signal__sck.h"
//#include "mega8/signal__ss.h"
#include "signal.h"


// user signals
#include "signal__pwm.h"
#include "signal__led.h"


#include "config__usart.h"
#include "config__spi.h"
#include "config__can.h"



// pwm

#define pwm_init() do {\
    PWM_DIR |= _BV(PWM_0_PIN)|_BV(PWM_1_PIN)|_BV(PWM_2_PIN)|_BV(PWM_3_PIN)|_BV(PWM_4_PIN)|_BV(PWM_5_PIN);\
} while(0)

#include "cpu/avr/m8__timer0.h"

#define pwm_start() do {\
    timer0__overflow_interrupt_enable();\
    timer0__start(TIMER0_MODE_RUN_NO_PRESCALER);\
} while(0)

#define pwm_stop() do {\
    timer0__stop();\
    timer0__overflow_interrupt_disable();\
} while(0)


#endif