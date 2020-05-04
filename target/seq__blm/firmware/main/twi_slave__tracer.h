#ifndef DRIVERS__COMM__TWI_SLAVE__TRACER_H
#define DRIVERS__COMM__TWI_SLAVE__TRACER_H

#include <stdint.h>

void twi__slave__tracer__status(uint8_t status);

void twi__slave__tracer__on_data_reception_started(uint8_t data);
void twi__slave__tracer__on_data_byte_received(uint8_t data);
void twi__slave__tracer__on_data_reception_finished(uint8_t data);

void twi__slave__tracer__on_data_byte_requested();
void twi__slave__tracer__on_data_byte_transmitted();

#endif
