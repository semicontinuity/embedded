#ifndef CONTACTOR_CONTROLLER__H
#define CONTACTOR_CONTROLLER__H


#include <stdbool.h>


bool contactor_controller__is_runnable(void);
void contactor_controller__run(void);

void contactor_controller__actual_state_renderer__run(void);


#endif