// =============================================================================
// Driver for OneWire bus on the specified ONEWIRE pin.
// Implemented with bit-banging and timer 2.
// Logical 1 is driven by external pull-up resistor
// (pin is switched to input).
// =============================================================================


void onewire__init(void);

void onewire__shutdown(void);

void onewire__send_bit_0(void);

void onewire__send_bit_1(void);

void onewire__receive_bit(void);
