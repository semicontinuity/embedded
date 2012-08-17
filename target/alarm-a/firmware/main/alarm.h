#ifndef __ALARM_H
#define __ALARM_H

#include "device.h"
#include <avr/pgmspace.h>

/**************************************/
/* Service functions                  */
/**************************************/
void alarm__run(void);

/**************************************/
/* Callbacks                          */
/**************************************/
void alarm_notification(void);

#endif
    