void sysex_blm__handle_ping();
void sysex_blm__handle_invalid_command();
void sysex_blm__handle_request_layout_info();

void sysex_blm__handle_ping() {
    sysex_blm__send_ack();
}

void sysex_blm__handle_invalid_command() {
    sysex_blm__send_nack();
}

void sysex_blm__handle_request_layout_info() {
    sysex_blm__send_layout_info();
}
