// =============================================================================
// Zero cross detector driver.
// Attached to INT0 pin, low-to-high transition shortly after zero cross.
// =============================================================================

#include "zero_cross_detector.h"
#include <avr/interrupt.h>


ISR(INT0_vect) {
    on_zero_cross();
}
