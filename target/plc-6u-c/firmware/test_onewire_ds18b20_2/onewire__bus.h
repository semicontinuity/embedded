// -----------------------------------------------------------------------------
// 1-wire driver, bus interface
// -----------------------------------------------------------------------------

#include <stdbool.h>
#include <stdint.h>

void onewire__bus__init(void);
void onewire__bus__set(const uint8_t value);
bool onewire__bus__get(void);
