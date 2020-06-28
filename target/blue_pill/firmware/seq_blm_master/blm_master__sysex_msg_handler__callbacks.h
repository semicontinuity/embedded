#include <stdint.h>

void blm_master__sysex_msg_handler__handle_invalid_command();
void blm_master__sysex_msg_handler__handle_ping();
void blm_master__sysex_msg_handler__handle_request_layout_info();
void blm_master__sysex_msg_handler__handle_set_palette_data(uint8_t palette, uint8_t *data, int32_t length);
