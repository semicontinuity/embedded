#ifndef ALERT_CONTROLLER__H
#define ALERT_CONTROLLER__H

#include <stdbool.h>


void alerting__failure__contactor_controller__push(bool value);

void alerting__failure__valve_controller__1__push(bool value);

void alerting__failure__prophylactic_engagement_controller__push(bool value);


bool alert_controller__has_water_alerts(void);


void alert_controller__run(void);


#endif