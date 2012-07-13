#ifndef __DEVICE_H
#define __DEVICE_H

#define F_CPU 12000000UL

#include "signal/mt12864.h"
#include "signal/lcd_backlight.h"

#include "cpu/avr/gpio.h"
#include "keyboard-connection.h"
#include "lcd-backlight-config.h"
#include "sensors-config.h"



// Ports
//
// PA - mt12864 data bus
// PB - keyboard
// PC
//   PC0  A0				OUT
//   PC1  RES				OUT
//   PC2  BT1				IN, int. pull up
//   PC3  BT2				IN, int. pull up
//   PC4  BT3				IN, int. pull up
//   PC5  BT4				IN, int. pull up
//   PC6  E1(was switched) = CS1	OUT
//   PC7  E2(was switched) = CS2	OUT
// PD
//   PD0  txd				OUT (future)
//   PD1  rxd				IN  (future)  int. pull up
//   PD2  STATE_CHANGE			OUT
//   PD3  (INT1) ALARM_STATE		IN  
//   PD4  LED				OUT
//   PD5  RD/WR				OUT
//   PD6  E				OUT
//   PD7  BACKLIGHT			OUT


//                                       +--------+
//                                   PD7 |21    20| PD6
//                                   PC0 |22    19| PD5
//                                   PC1 |23    18| PD4    x-[]--x  armed LED, out
//                                   PC2 |24    17| PD3    x-[]--x  alarm state, in
//                                   PC3 |25    16| PD2    x--##-x  state change, out
//                                   PC4 |26    15| PD1      -##
//                                   PC5 |27    14| PD0
//                                   PC6 |28    13| xtal1
//                                   PC7 |29    12| xtal2
//                                  AVCC |30    11| GND
//                                   GND |31    10| VCC
//                                  AREF |32     9| RESET
//                                   PA7 |33     8| PB7
//                                       |34     7|
//                                       |35     6|
//                                       |36     5|
//                                       |37     4|
//                                       |38     3|
//                                       |39     2|
//                                   PA0 |40  O  1| PB0
//                                       +--------+
//                                         +----+
//                                         |    |
//                                         +----+
//                                         AVR ISP

#define PERIODIC_INTERRUPT_VECT    (TIMER0_OVF_vect)
#define ALARM_STATE_INTERRUPT_VECT (INT1_vect)

// Signal ALARM_STATE, input
// Port PD3, used as INT1 (?)
// Input from alarm base station to indicate the current state of alarm
#define SIG_ALARM_STATE_PORT (PORTD)
#define SIG_ALARM_STATE_DIR  (DDRD)
#define SIG_ALARM_STATE_PIN  (3)
#define is_system_armed() bit_is_set(PIND, SIG_ALARM_STATE_PIN)

// Signal STATE_CHANGE, output
// Port PD2
// External inverting transistor connected
// Output signalling a state change (as a short negative pulse), when correct password is entered
#define SIG_STATE_CHANGE_PORT (PORTD)
#define SIG_STATE_CHANGE_DIR  (DDRD)
#define SIG_STATE_CHANGE_PIN  (2)

#define state_change_low()  set_bit_in_reg(SIG_STATE_CHANGE_PORT,SIG_STATE_CHANGE_PIN)
#define state_change_high() clear_bit_in_reg(SIG_STATE_CHANGE_PORT,SIG_STATE_CHANGE_PIN)

// Uart (not used at the moment)
#define SIG_TXD_PORT (PORTD)
#define SIG_TXD_DIR  (DDRD)
#define SIG_TXD_PIN  (1)

#define SIG_RXD_PORT (PORTD)
#define SIG_RXD_DIR  (DDRD)
#define SIG_RXD_PIN  (0)

// Led is attached to PD4
#define SIG_LED_PORT (PORTD)
#define SIG_LED_DIR  (DDRD)
#define SIG_LED_PIN  (4)
#define armed_led_on()      set_bit_in_reg (SIG_LED_PORT, SIG_LED_PIN)
#define armed_led_off()     clear_bit_in_reg (SIG_LED_PORT, SIG_LED_PIN)




// (Configure ALARM_STATE for input: do nothing, input by default)
// 1. Pull up ALARM_STATE
// 2. Configure STATE_CHANGE for input
// (Not necessarry to pull up STATE_CHANGE, it has external pull up)
// 3. Configure Txd for output
// 4. Pull up Rxd (save some power)
// 5. Configure LED for output
// (PORTA is configured separetely - for mt12864 data bus)
// (PORTB is configured separetely - for keyboard)
// (PC2-PC5 configured separetely - for sensors)
// (mt12864 control lines configured separetely)


#define configure_io() do {\
    set_bit_in_reg (SIG_ALARM_STATE_PORT, SIG_ALARM_STATE_PIN);\
    set_bit_in_reg (SIG_STATE_CHANGE_DIR, SIG_STATE_CHANGE_PIN);\
    set_bit_in_reg (SIG_TXD_DIR, SIG_TXD_PIN);\
    set_bit_in_reg (SIG_RXD_PORT, SIG_RXD_PIN);\
    set_bit_in_reg (SIG_LED_DIR, SIG_LED_PIN);\
} while(0)

// 1. any change on INT1 generates interrupt (ISC11=0 (default), ISC10=1)
// 2. enable ext int 1
#define configure_ext_interrupts() do {\
    set_bit_in_reg (MCUCR, ISC10);\
    set_bit_in_reg (GICR, INT1);\
} while(0)

// 1. enable TIMER0_OVF_vect
// 2. no Force Output Compare, WGMxx=NORMAL, Normal operation, OC0 disconnected, f=clkIO/1024
#define init_and_start_scheduler() do {\
    TIMSK = _BV (TOIE0);\
    TCCR0 = _BV (CS02) | _BV(CS00);\
} while(0)

#endif