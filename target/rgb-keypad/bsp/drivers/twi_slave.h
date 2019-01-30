#ifndef DRIVERS__TWI_SLAVE_H
#define DRIVERS__TWI_SLAVE_H

#include <stdbool.h>

bool twi_slave__thread__is_runnable(void);
void twi_slave__thread__run(void);

#endif
