#ifndef __SERVICES__TEMPERATURE_READER_H
#define __SERVICES__TEMPERATURE_READER_H

#include <stdint.h>
#include <stdbool.h>

void temperature_reader__on_measurement(const uint8_t sensor, const uint16_t value);

void temperature_reader__thread__start(void);

bool temperature_reader__thread__is_runnable(void);

void temperature_reader__thread__run(void);

#endif