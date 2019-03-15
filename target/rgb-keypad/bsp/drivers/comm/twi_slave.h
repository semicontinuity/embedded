#ifndef DRIVERS__COMM__TWI_SLAVE_H
#define DRIVERS__COMM__TWI_SLAVE_H

#include <stdbool.h>

void twi__slave__thread__init(void);
void twi__slave__thread__start(void);
bool twi__slave__thread__is_runnable(void);
void twi__slave__thread__run(void);

#endif
