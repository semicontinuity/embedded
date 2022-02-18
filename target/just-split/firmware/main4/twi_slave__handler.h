#ifndef DRIVERS__COMM__TWI_SLAVE_H
#define DRIVERS__COMM__TWI_SLAVE_H

#include <stdbool.h>

bool twi__slave__handler__is_runnable(void);
void twi__slave__handler__run(void);

#endif
