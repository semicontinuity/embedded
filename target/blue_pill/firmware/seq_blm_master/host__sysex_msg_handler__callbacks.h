#include <stdint.h>

void host__sysex_msg_handler__handle_invalid_command();
void host__sysex_msg_handler__handle_ping();
void host__sysex_msg_handler__handle_request_layout_info();
void host__sysex_msg_handler__handle_set_palette_data(uint8_t palette, uint8_t *data, int32_t length);
