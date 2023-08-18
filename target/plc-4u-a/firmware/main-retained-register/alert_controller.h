#ifndef ALERT_CONTROLLER__H
#define ALERT_CONTROLLER__H

#include <stdbool.h>


void alerting__failure__contactor_controller__set(bool value);
bool alerting__failure__contactor_controller__get(void);


void alarm_controller__run(void);


#endif