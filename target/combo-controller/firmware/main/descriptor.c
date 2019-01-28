#include "descriptor.h"
#include <avr/pgmspace.h>

const uint8_t descriptor__value[] PROGMEM = {
};

const uint8_t* const descriptor__address __attribute__((section(".descriptor__address"))) = descriptor__value;
