#ifndef __DEVICE_H
#define __DEVICE_H

#include "cpu/avr/gpio.h"


#include "config/usart.h"
#include "config/alarm.h"


#define SWITCH_A_PORT          (PORTD)
#define SWITCH_A_DIR           (DDRD)
#define SWITCH_A_PIN           (5)
#define switch_a_init()        set_bit_in_reg (SWITCH_A_DIR, SWITCH_A_PIN)
#define switch_a_on()          set_bit_in_reg (SWITCH_A_PORT, SWITCH_A_PIN)
#define switch_a_off()         clear_bit_in_reg (SWITCH_A_PORT, SWITCH_A_PIN)


#define SWITCH_B_PORT          (PORTB)
#define SWITCH_B_DIR           (DDRB)
#define SWITCH_B_PIN           (7)
#define switch_b_init()        set_bit_in_reg (SWITCH_B_DIR, SWITCH_B_PIN)
#define switch_b_on()          set_bit_in_reg (SWITCH_B_PORT, SWITCH_B_PIN)
#define switch_b_off()         clear_bit_in_reg (SWITCH_B_PORT, SWITCH_B_PIN)


// Scheduler uses TIMER0_OVF_vect, enable it.
// CS=100, CLKio/256
// Interrupt will be invoked F_CPU/256/256 times per second
#define init_and_start_scheduler() do {\
    TIMSK0 = _BV (TOIE0);\
    TCCR0B = _BV (CS02);\
} while(0)


#define alarm_on()              do { alarm_out_pin_high(); switch_b_on(); } while(0)
#define alarm_off()             do { alarm_out_pin_low(); switch_b_off(); } while(0)


#endif