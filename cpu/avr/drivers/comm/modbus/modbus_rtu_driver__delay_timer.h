// =============================================================================
// MODBUS RTU driver.
// Delay timer for handling of 1.5 and 3.5 character timeouts
// during USART data reception.
// =============================================================================

#ifndef CPU__AVR__DRIVERS__COMM__MODBUS__MODBUS_RTU_DRIVER__DELAY_TIMER_H
#define CPU__AVR__DRIVERS__COMM__MODBUS__MODBUS_RTU_DRIVER__DELAY_TIMER_H


#include <avr/interrupt.h>
#include <stdint.h>


void modbus_rtu_driver__delay_timer__configure(const uint16_t t15, const uint16_t t35);

void modbus_rtu_driver__delay_timer__start(void);

void modbus_rtu_driver__delay_timer__stop(void);

/** Callback to be implemented */
void modbus_rtu_driver__delay_timer__on_t15_expired(void);

/** Callback to be implemented */
void modbus_rtu_driver__delay_timer__on_t35_expired(void);

#endif