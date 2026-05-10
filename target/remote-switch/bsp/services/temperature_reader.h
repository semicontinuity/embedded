#ifndef __SERVICES__TEMPERATURE_READER_H
#define __SERVICES__TEMPERATURE_READER_H

#include <stdint.h>
#include <stdbool.h>

extern uint16_t temperature_reader__reading;

void temperature_reader__reading__on_changed(void);

void temperature_reader__thread__start(void);

bool temperature_reader__thread__is_runnable(void);

void temperature_reader__thread__run(void);

#endif