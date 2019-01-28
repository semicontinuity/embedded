#ifndef __MODULE_DESCRIPTOR_H
#define __MODULE_DESCRIPTOR_H

#include <avr/pgmspace.h>
#include <stdint.h>

extern const uint8_t module_descriptor__value[] __attribute__((section(".module_descriptor__value")));
extern const uint8_t* const module_descriptor__address __attribute__((section(".module_descriptor__address")));

#endif