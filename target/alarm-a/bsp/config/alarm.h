#ifndef __ALARM_CONFIG_H
#define __ALARM_CONFIG_H

#include "cpu/avr/gpio.h"

// ALARM_STATE pin, PC2, output
// Communicates to terminals the state of the system (high=system armed)
#define ALARM_STATE_PORT        (PORTC)
#define ALARM_STATE_DIR         (DDRC)
#define ALARM_STATE_PIN         (2)
#define alarm_state_pin_init()  set_bit_in_reg (ALARM_STATE_DIR, ALARM_STATE_PIN)
#define alarm_state_armed()     set_bit_in_reg (ALARM_STATE_PORT, ALARM_STATE_PIN)
#define alarm_state_disarmed()  clear_bit_in_reg (ALARM_STATE_PORT, ALARM_STATE_PIN)


#endif