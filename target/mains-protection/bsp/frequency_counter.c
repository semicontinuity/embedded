// =============================================================================
// Mains frequency counter.
// =============================================================================

#include "frequency_counter.h"

/**
 * The measured frequency * 10.
 * The mains frequency is measured during 10 seconds intervals.
 */
volatile uint16_t frequency;

/**
 * Called every 10 seconds to reset the measurement.
 * Must be called after the measurement has been read.
 */
INLINE void frequency_counter__reset(void) {
    frequency = 0;    
}


/**
 * Called on every zero cross.
 */
INLINE void frequency_counter__run(void) {
    frequency = 0;    
}
