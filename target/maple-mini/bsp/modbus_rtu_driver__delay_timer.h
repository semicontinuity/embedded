// =============================================================================
// MODBUS RTU driver.
// Delay timer for handling of 1.5 and 3.5 character timeouts
// during USART data reception.
// =============================================================================

#ifndef MODBUS_RTU_DRIVER__DELAY_TIMER_H
#define MODBUS_RTU_DRIVER__DELAY_TIMER_H


#include <stdint.h>


void modbus_rtu_driver__delay_timer__init(void);

void modbus_rtu_driver__delay_timer__start(void);

void modbus_rtu_driver__delay_timer__stop(void);

/** Callback to be implemented */
void modbus_rtu_driver__delay_timer__on_t15_expired(void);

/** Callback to be implemented */
void modbus_rtu_driver__delay_timer__on_t35_expired(void);

#endif