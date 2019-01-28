// =============================================================================
// Water counter driver.
//
// Hardware connections:
//
// [+5V] --- [ 4k7 ] --- [ AIN1 ] --- [Counter] --- [GND]
// =============================================================================

#ifndef __DRIVERS__WATER_COUNTER_H
#define __DRIVERS__WATER_COUNTER_H

#include <stdbool.h>
#include <stdint.h>
#include <avr/io.h>


void water_counter__init(void);

void water_counter__start(void);


#endif