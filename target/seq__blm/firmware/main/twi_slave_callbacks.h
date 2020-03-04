#ifndef DRIVERS__COMM__TWI_SLAVE_CALLBACKS_H
#define DRIVERS__COMM__TWI_SLAVE_CALLBACKS_H

#include <stdbool.h>

/**
 * handler must set data byte to be transmitted with twi__data__set(),
 * and then call twi__continue(true, false) if non-last data byte has to be transmitted
 * or twi__continue(false, false) if last data byte has to be transmitted.
 */
void twi__slave__on_data_byte_requested(void);

/**
 * handler must call twi__continue(true, false) if more than 1 data byte should be received
 * handler must call twi__continue(false, false) if the only data byte should be received
 */
void twi__slave__on_data_reception_started(void);

/**
 * handler must call twi__continue(true, false) if more than 1 data byte remains to be received
 * handler must call twi__continue(false, false) if the last data byte should be received
 */
void twi__slave__on_data_byte_received(uint8_t value);

/**
 * handler must call twi__continue(true, false)
 */
void twi__slave__on_data_reception_finished(void);

#endif
