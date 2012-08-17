#ifndef __ALARM_CONFIG_H
#define __ALARM_CONFIG_H

#include "cpu/avr/gpio.h"


// SENSOR_LINE pin, PB3, input, ext. pullup
// Any sensor may drive it low to indicate alarm condition
#define SENSOR_LINE_PORT_IN	(PINB)
#define SENSOR_LINE_DIR		(DDRB)
#define SENSOR_LINE_PIN		(3)
#define sensor_line_pin_init()
#define intruder_detected()     (bit_is_clear(SENSOR_LINE_PORT_IN,SENSOR_LINE_PIN))

// ALARM_OUT pin, PB5, output, active high
// May be used to trigger external sound alarm
#define ALARM_OUT_PORT          (PORTB)
#define ALARM_OUT_DIR           (DDRB)
#define ALARM_OUT_PIN           (5)
#define alarm_out_pin_init()    set_bit_in_reg (ALARM_OUT_DIR, ALARM_OUT_PIN)
#define alarm_out_pin_low()     clear_bit_in_reg (ALARM_OUT_PORT, ALARM_OUT_PIN)
#define alarm_out_pin_high()    set_bit_in_reg (ALARM_OUT_PORT, ALARM_OUT_PIN)

// ALARM_STATE pin, PC2, output
// Communicates to terminals the state of the system (high=system armed)
#define ALARM_STATE_PORT        (PORTC)
#define ALARM_STATE_DIR         (DDRC)
#define ALARM_STATE_PIN         (2)
#define alarm_state_pin_init()  set_bit_in_reg (ALARM_STATE_DIR, ALARM_STATE_PIN)
#define alarm_state_armed()     set_bit_in_reg (ALARM_STATE_PORT, ALARM_STATE_PIN)
#define alarm_state_disarmed()  clear_bit_in_reg (ALARM_STATE_PORT, ALARM_STATE_PIN)


#endif