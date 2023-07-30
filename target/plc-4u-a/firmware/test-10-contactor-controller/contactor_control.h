#ifndef CONTACTOR_CONTROL__H
#define CONTACTOR_CONTROL__H


#include <stdbool.h>


bool contactor_control__is_runnable(void);
void contactor_control__run(void);

void contactor_control__actual_state_renderer__run(void);


#endif