#ifndef DRIVERS__COMM__TWI_SLAVE_CALLBACKS_H
#define DRIVERS__COMM__TWI_SLAVE_CALLBACKS_H

#include <stdbool.h>

/**
 * handler must set data byte to be transmitted with twi__data__set(),
 * and then call twi__continue(true, false); if non-last data byte has to be transmitted
 * or twi__continue(false, false); if last data byte has to be transmitted.
 */
void twi__slave__on_data_byte_requested(void);

void twi__slave__on_data_reception_started(void);
void twi__slave__on_data_byte_received(uint8_t value);

#endif
