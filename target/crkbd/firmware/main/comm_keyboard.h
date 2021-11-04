#ifndef COMM_KEYBOARD_H
#define COMM_KEYBOARD_H

#include <stdbool.h>

void comm_keyboard__thread__start(void);

bool comm_keyboard__thread__is_runnable(void);

void comm_keyboard__thread__run(void);

#endif
