#ifndef __DEVICE_H
#define __DEVICE_H

#include "cpu/avr/gpio.h"

// 8 MHz (internal calibrated RC oscillator)
// It is chosen to provide minimal error for USART at 19200
// It is also possible to run from external clock (should be 4MHz)
#define F_CPU (8000000UL)

// Connector, front view
//
//        state      GND 5V
// +--+--+--+--+--+--+--+--+--+--+
// |AVR ISP |  |WATER|  |  |rx|tx|
// +        +--+--+--+--+--+--+--+
// |1       |in|   VCC  |  GND   |
// +--+--+--+--+--+--+--+--+--+--+
// [======= bottom (board) ======]
//
// in = STATE_CHANGE (from terminals - notify with short negative pulse)
// state = ALARM_STATE (high=armed, low=disarmed)
//
// AVR ISP=               Alarm pins=
// +----+----+----+       +----+----+----+
// |VTG |MOSI|GND |       |    |sens|    |
// +----+----+----+       +----+----+----+
// |MISO|SCK |RST |       |    |alrm|    |
// +----+----+----+       +----+----+----+


// Ports
// PB0 STATE_CHANGE		pin 12 - input, externally pulled up
// PB1
// PB2 
// PB3 mosi + SENSOR_LINE	input, externally pulled up. Active low.
// PB4 miso
// PB5 sck + ALARM_OUT		output, active high
// PB6 water B			input, active low
// PB7 switch B			output, active high
// PC0
// PC1
// PC2 ALARM_STATE		output, high=armed
// PC3
// PC4
// PC5
// PC6 reset
// PD0 rx
// PD1 tx
// PD2
// PD3
// PD4 water A			input, active low
// PD5 switch A			output, active high
// PD6
// PD7

#include "config/usart.h"
#include "config/alarm.h"



#define WATER_SENSOR_A_PORT_IN       (PIND)
#define WATER_SENSOR_A_DIR           (DDRD)
#define WATER_SENSOR_A_PIN           (4)
#define water_sensor_a_init()        
#define water_leak_a()               (bit_is_clear(WATER_SENSOR_A_PORT_IN,WATER_SENSOR_A_PIN))


#define WATER_SENSOR_B_PORT_IN       (PINB)
#define WATER_SENSOR_B_DIR           (DDRB)
#define WATER_SENSOR_B_PIN           (6)
#define water_sensor_b_init()        
#define water_leak_b()               (bit_is_clear(WATER_SENSOR_B_PORT_IN,WATER_SENSOR_B_PIN))



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


// As inputs with pull-ups
#define configure_unused_ports() do {\
  set_bit_in_reg (DDRB, 1);\
  set_bit_in_reg (DDRB, 2);\
  set_bit_in_reg (DDRB, 4);\
  set_bit_in_reg (DDRC, 0);\
  set_bit_in_reg (DDRC, 1);\
  set_bit_in_reg (DDRC, 3);\
  set_bit_in_reg (DDRC, 4);\
  set_bit_in_reg (DDRC, 5);\
  set_bit_in_reg (DDRC, 6);\
  set_bit_in_reg (DDRD, 2);\
  set_bit_in_reg (DDRD, 3);\
  set_bit_in_reg (DDRD, 6);\
  set_bit_in_reg (DDRD, 7);\
} while(0)


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