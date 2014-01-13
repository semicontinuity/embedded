// =============================================================================
// Pool controller extender - main module.
// =============================================================================

#include <avr/interrupt.h>
#include "drivers/buttons.h"
#include "drivers/hd44780_watcher.h"


// =============================================================================
// Application
// =============================================================================

inline static void application__init(void) {    
    buttons__init();
    hd44780_watcher__init();
}


// =============================================================================
// Entry point.
// =============================================================================
int main(void) {
    application__init();

    sei();

    for(;;);
    return 0;
}
