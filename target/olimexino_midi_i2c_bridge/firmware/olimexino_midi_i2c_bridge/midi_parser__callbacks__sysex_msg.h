#include <stdint.h>

void midi_parser__on_sysex_data(uint8_t data);
void midi_parser__on_sysex_finish();
void midi_parser__on_sysex_error();
