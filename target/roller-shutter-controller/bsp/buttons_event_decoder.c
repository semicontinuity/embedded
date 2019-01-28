// =============================================================================
// The event decoder for 2 buttons at pins BUTTON1 and BUTTON2.
// The buttons must connected to the same port.
// =============================================================================
#include "buttons_event_decoder.h"

uint8_t buttons_event_decoder__pending;
uint8_t buttons_event_decoder__state;
uint8_t buttons_event_decoder__mask = SIGNAL_MASK(BUTTON1);
