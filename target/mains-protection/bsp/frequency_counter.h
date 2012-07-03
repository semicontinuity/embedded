#ifndef __FREQUENCY_COUNTER_H
#define __FREQUENCY_COUNTER_H

#include <stdint.h>

/**
 * The measuread frequency * 10.
 * The mains frequency is measured during 10 seconds intervals.
 */
extern volatile uint16_t frequency;


/**
 * Called every 10 seconds to reset the measurement.
 * Must be called after the measurement has been read.
 */
INLINE void frequency_counter__reset(void);


/**
 * Called on every zero cross.
 */
INLINE void frequency_counter__run(void);


#endif