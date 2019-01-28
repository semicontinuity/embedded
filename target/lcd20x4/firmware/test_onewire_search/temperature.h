#ifndef __TEMPERATURE_H_
#define __TEMPERATURE_H_
#include <stdint.h>

#include "1-wire/ds18x20.h"
#include "1-wire/onewire.h"

extern uint8_t id[OW_ROMCODE_SIZE];

uint8_t start_OW(void);
void temperature_init(void);

#endif
