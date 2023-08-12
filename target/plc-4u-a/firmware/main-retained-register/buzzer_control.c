// =============================================================================
// Buzzer controller
// =============================================================================
#include "buzzer_control.h"
#include "services/internal_coils.h"


// Buzzer timeout in seconds
uint8_t buzzer__timeout;


// Must be invoked on every tick of fast timer (every1 ms)
void buzzer_controller__on_fast_timer_tick(void) {
}


// Must be invoked every second
void buzzer_controller__run(void) {
}
