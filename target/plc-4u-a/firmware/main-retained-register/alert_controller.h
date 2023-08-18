#ifndef ALERT_CONTROLLER__H
#define ALERT_CONTROLLER__H

#include <stdbool.h>


bool alerting__failure__contactor_controller__get(void);
void alerting__failure__contactor_controller__push(bool value);

bool alerting__failure__valve_controller__1__get(void);
void alerting__failure__valve_controller__1__push(bool value);

void alert_controller__run(void);


#endif