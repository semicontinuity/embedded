#ifndef CONTACTOR_CONTROL__H
#define CONTACTOR_CONTROL__H


#include <stdbool.h>


void contactor_control__error__set(bool value);
bool contactor_control__error__get(void);

bool contactor_control__is_runnable(void);
void contactor_control__run(void);

void contactor_control__actual_state_renderer__run(void);


#endif